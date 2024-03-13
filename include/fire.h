#include "api.h"
#include "liblvgl/lvgl.h"
#include <functional>
#include <string>
#include <vector>


namespace fire {
  inline pros::Controller cont(pros::E_CONTROLLER_MASTER);
  inline int delay = 10;

  enum pid_types { Drive, Turn, Swing };

  enum swing_type { Left, Right };

  // lcd class to manage all methods related to the screen
  class lcd {
    // tell if the screen has been setup and ready to use
    inline static bool initialized = false;
    // screen to draw to
    inline static lv_obj_t *console = nullptr;
    // label for text
    inline static lv_obj_t *console_text = nullptr;

    inline static std::string display[14] = {"", "", "", "", "", "", "",
                                            "", "", "", "", "", "", ""};

  public:
    // set up the screen to draw
    static void initialize();

    // allow printing to the screen
    static void print(std::string str);

    static void println(int line, std::string str);

    // clear the screen
    static void clear();
  };

  // drive class to manage all robot movement
  class drive {
  public:
    std::vector<pros::Motor> left_drive;
    std::vector<pros::Motor> right_drive;

    drive(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports,
          int imu_port, int motor_rpm, float gear_ratio, float wheel_diameter) {
      // create left drive motors
      for (int i = 0; i < left_motor_ports.size(); i++) {
        left_drive.push_back(pros::Motor(left_motor_ports[i]));
        left_drive[i].set_encoder_units(pros::MotorEncoderUnits::rotations);
        left_targets.push_back(0.0);
        left_prev_errors.push_back(0.0);
        left_total_error.push_back(0.0);
      }
      // create right drive motors
      for (int i = 0; i < right_motor_ports.size(); i++) {
        right_drive.push_back(pros::Motor(right_motor_ports[i]));
        right_drive[i].set_encoder_units(pros::MotorEncoderUnits::rotations);
        right_targets.push_back(0.0);
        right_prev_errors.push_back(0.0);
        right_total_error.push_back(0.0);
      }
      // set IMU
      imu._port = imu_port;

      // set the motor's rpm
      rpm = motor_rpm;
      // set the drive gear ratio
      gearRatio = gear_ratio;
      // set the wheel diameter (inches)
      diameter = wheel_diameter;
    };

    pros::Imu imu = pros::Imu(0);

    // driver control types
    // left stick is left drive, Right stick is right drive
    void tank_control();
    // Left stick is fwd or rev, Right stick is turning
    void split_arcade();
    // Right stick is fwd or rev, Left stick is turning
    void split_arcade_flipped();
    // set brake for all motors
    void set_break_mode(pros::MotorBrake mode);

    // drive info
    std::vector<float> left_targets;
    std::vector<float> right_targets;

    std::vector<float> left_prev_errors;
    std::vector<float> right_prev_errors;

    std::vector<float> left_total_error;
    std::vector<float> right_total_error;

    float deg_target = 0.0;
    float deg_prev_error = 0.0;
    float deg_total_error = 0.0;

    int rpm;
    float gearRatio;
    float diameter;
    int speed;

    float drive_Kp = 0.0;
    float drive_Ki = 0.0;
    float drive_Kd = 0.0;
    float turn_Kp = 0.0;
    float turn_Ki = 0.0;
    float turn_Kd = 0.0;
    // exit conditions
    // drive
    float drive_small_error;
    float drive_large_error;
    int drive_small_timeout;
    int drive_large_timeout;
    int drive_zero_timeout;
    // turn
    float turn_small_error;
    float turn_large_error;
    int turn_small_timeout;
    int turn_large_timeout;
    int turn_zero_timeout;
    // swing
    float swing_small_error;
    float swing_large_error;
    int swing_small_timeout;
    int swing_large_timeout;
    int swing_zero_timeout;
    // drive adjustments
    float start_deg = 0;
    float rots_per_degs = 0.00;  // 1/20 rotation for every 1 degree off
                                // unlike pids, this is required to be tuned

    //      Autonomous PID Controls
    void init_pids();

    //
    //  PID TASK INFO
    //
    enum pid_state { None, Drive, Turn, Swing };

    pid_state current_pid_state = pid_state::None;

    static void drive_pid_task(void *c);

    // Stop any current pid
    void stop_pid();

    // exit conditions
    void set_exit_conditions(fire::pid_types pid_type, float small_error,
                            float large_error, int small_timeout,
                            int large_timeout, int zero_timeout);

    void set_pid(fire::pid_types pid_type, float kp, float ki, float kd);

    // wait for current drive conditions to be met
    void wait_drive();

    // wait until certain conditions such as degree or inch is met
    void wait_until(double target);

    // set the target for the drive
    void set_drive_pid(float distance, int speed);

    // set the target for turning
    void set_turn_pid(float deg, int speed);

    // set the tank speeds to control drive outside of pid
    void set_tank(int left, int right);

    // active braking info
    void set_active_breaking(float kp);
    void init_active_breaking();
    static void active_breaking_task(void *c);

    float active_breaking_kp = 0.0;

    // detect and calibrate imu
    void calibrate_imu();
  };

  class as {
    private:
      inline static lv_obj_t *screen = nullptr;
      inline static lv_obj_t *page_num = nullptr;
      inline static lv_obj_t * a1_text = nullptr;
      inline static lv_obj_t * a2_text = nullptr;
      inline static lv_obj_t * a3_text = nullptr;
      inline static lv_obj_t * a4_text = nullptr;
      inline static lv_obj_t * a5_text = nullptr;
      inline static lv_obj_t * Auton1 = nullptr;
      inline static lv_obj_t * Auton2 = nullptr;
      inline static lv_obj_t * Auton3 = nullptr;
      inline static lv_obj_t * Auton4 = nullptr;
      inline static lv_obj_t * Auton5 = nullptr;
      inline static lv_obj_t * selected = nullptr;
      inline static int current_page = 0;
      inline static int page_limit = 0;

      static void next_handle(lv_event_t * e);
      static void prev_handle(lv_event_t * e);
      static void select_handle(lv_event_t * e);

    public:
      class Auton {
      public:
        std::string name;
        std::function<void()> func;

        Auton(std::string name, std::function<void()> function) {
          this->name = name;
          this->func = function;
        }
      };

      static inline std::vector<Auton> autons = {};
      static inline int index = -1;

      static void add_autons(std::vector<Auton> auton_list);

      static void init_selector();

      static void page_up();

      static void page_down();

      static void call_selected_auton();

      static void set_visible(bool visible);
  };
} // namespace fire
