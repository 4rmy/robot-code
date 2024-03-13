#include "fire.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.h"
#include <cmath>
#include <string>

// DRIVE CONTROLS
void fire::drive::tank_control() {
  // get speeds from analog sticks
  int left_speed = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right_speed = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // apply left speed to left motors
  for (int i = 0; i < left_drive.size(); i++) {
    left_drive[i] = left_speed;
  }

  // apply right speed to right motors
  for (int i = 0; i < right_drive.size(); i++) {
    right_drive[i] = right_speed;
  }
}

void fire::drive::split_arcade() {
  // get speeds from analog sticks
  int fwd_rev = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int left_right = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  // apply left speed to left motors
  for (int i = 0; i < left_drive.size(); i++) {
    left_drive[i] = fwd_rev + left_right;
  }

  // apply right speed to right motors
  for (int i = 0; i < right_drive.size(); i++) {
    right_drive[i] = fwd_rev - left_right;
  }
}

void fire::drive::split_arcade_flipped() {
  // get speeds from analog sticks
  int fwd_rev = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  int left_right = fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

  // apply left speed to left motors
  for (int i = 0; i < left_drive.size(); i++) {
    left_drive[i] = fwd_rev + left_right;
  }

  // apply right speed to right motors
  for (int i = 0; i < right_drive.size(); i++) {
    right_drive[i] = fwd_rev - left_right;
  }
}

void fire::drive::set_break_mode(pros::MotorBrake mode) {
  for (int i = 0; i < this->left_drive.size(); i++) {
    this->left_drive[i].set_brake_mode(mode);
  }
  for (int i = 0; i < this->right_drive.size(); i++) {
    this->right_drive[i].set_brake_mode(mode);
  }
}

// AUTONOMOUS PID CONTROLS

void fire::drive::init_pids() {
  this->imu.tare();
  pros::Task(this->drive_pid_task, (void *)this, TASK_PRIORITY_DEFAULT,
             TASK_STACK_DEPTH_DEFAULT, "PID Task");
}

/*
        DRIVE PID TASK
*/
void fire::drive::drive_pid_task(void *c) {
  while (true) {
    if (((fire::drive *)c)->current_pid_state ==
        fire::drive::pid_state::Drive) {
      float deg_err = ((fire::drive *)c)->imu.get_rotation() -
                      ((fire::drive *)c)->start_deg;
      float adjustment = ((fire::drive *)c)->rots_per_degs * deg_err;

      // calculate pid for each left motor
      for (int i = 0; i < ((fire::drive *)c)->left_drive.size(); i++) {
        // error calculation
        float error = ((fire::drive *)c)->left_targets[i] -
                      ((fire::drive *)c)->left_drive[i].get_position() +
                      adjustment; // ADJUST THIS IF NEEDED
        float diff = error - ((fire::drive *)c)->left_prev_errors[i];
        ((fire::drive *)c)->left_prev_errors[i] = error;
        ((fire::drive *)c)->left_total_error[i] += error;

        // p,i,d calculations
        float proportional = ((fire::drive *)c)->drive_Kp * error;
        float integral = ((fire::drive *)c)->drive_Ki *
                         ((fire::drive *)c)->left_total_error[i];
        float derivitive = ((fire::drive *)c)->drive_Kd * diff;

        // calc total power
        float power = proportional + integral + derivitive;

        float volts = power * ((fire::drive *)c)->speed;
        if (volts < -((fire::drive *)c)->speed) {
          volts = -127;
        } else if (volts > ((fire::drive *)c)->speed) {
          volts = 127;
        }

        ((fire::drive *)c)->left_drive[i] = volts;
      }

      // calculate pid for each right motor
      for (int i = 0; i < ((fire::drive *)c)->right_drive.size(); i++) {
        // error calculation
        float error = ((fire::drive *)c)->right_targets[i] -
                      ((fire::drive *)c)->right_drive[i].get_position() +
                      adjustment; // ADJUST THIS IF NEEDED
        float diff = error - ((fire::drive *)c)->right_prev_errors[i];
        ((fire::drive *)c)->right_prev_errors[i] = error;
        ((fire::drive *)c)->right_total_error[i] += error;

        // p,i,d calculations
        float proportional = ((fire::drive *)c)->drive_Kp * error;
        float integral = ((fire::drive *)c)->drive_Ki *
                         ((fire::drive *)c)->right_total_error[i];
        float derivitive = ((fire::drive *)c)->drive_Kd * diff;

        // calc total power
        float power = proportional + integral + derivitive;

        float volts = power * ((fire::drive *)c)->speed;
        if (volts < -((fire::drive *)c)->speed) {
          volts = -127;
        } else if (volts > ((fire::drive *)c)->speed) {
          volts = 127;
        }

        ((fire::drive *)c)->right_drive[i] = volts;
      }
    } else if (((fire::drive *)c)->current_pid_state ==
               fire::drive::pid_state::Turn) {
      float error = ((fire::drive *)c)->deg_target -
                    ((fire::drive *)c)->imu.get_rotation();
      float diff = error - ((fire::drive *)c)->deg_prev_error;
      ((fire::drive *)c)->deg_prev_error = error;
      ((fire::drive *)c)->deg_total_error += error;

      float proportional = ((fire::drive *)c)->turn_Kp * error;
      float integral =
          ((fire::drive *)c)->turn_Ki * ((fire::drive *)c)->deg_total_error;
      float derivitive = ((fire::drive *)c)->turn_Kd * diff;

      float power = proportional + integral + derivitive;

      float volts = power * ((fire::drive *)c)->speed;
      if (volts < -((fire::drive *)c)->speed) {
        volts = -127;
      } else if (volts > ((fire::drive *)c)->speed) {
        volts = 127;
      }

      for (int i = 0; i < ((fire::drive *)c)->left_drive.size(); i++) {
        ((fire::drive *)c)->left_drive[i] = volts;
      }
      for (int i = 0; i < ((fire::drive *)c)->right_drive.size(); i++) {
        ((fire::drive *)c)->right_drive[i] = -volts;
      }
    }
    pros::delay(fire::delay);
  }
}
/*
        DRIVE PID TASK
*/

void fire::drive::stop_pid() {
  this->current_pid_state = this->pid_state::None;
  this->set_tank(0, 0);
}

void fire::drive::wait_drive() {
  int zero_start = 0;
  int large_start = 0;
  int small_start = 0;
  bool zero_time = false;
  bool large_time = false;
  bool small_time = false;

  while (true) {
    if (this->current_pid_state == fire::drive::pid_state::Drive) {
      if (!zero_time) {
        zero_start = pros::millis();
      } else if (pros::millis() > zero_start + this->drive_zero_timeout) {
        break;
      }

      if (!large_time) {
        large_start = pros::millis();
      } else if (pros::millis() > large_start + this->drive_large_timeout) {
        break;
      }

      if (!small_time) {
        small_start = pros::millis();
      } else if (pros::millis() > small_start + this->drive_small_timeout) {
        break;
      }

      small_time = true;
      large_time = true;
      zero_time = true;
      for (int i = 0; i < this->left_drive.size(); i++) {
        float distance =
            std::abs((this->left_prev_errors[i] * (200 / this->gearRatio)) /
                     this->diameter);

        if (!(distance < this->drive_small_error)) {
          small_time = false;
        }
        if (!(distance < this->drive_large_error)) {
          large_time = false;
        }
      }
      for (int i = 0; i < this->right_drive.size(); i++) {
        int distance =
            std::abs((this->right_prev_errors[i] * (200 / this->gearRatio)) /
                     this->diameter);
        if (!(distance < this->drive_small_error)) {
          small_time = false;
        }
        if (!(distance < this->drive_large_error)) {
          large_time = false;
        }
      }
      float avg_speed = (this->imu.get_accel().x + this->imu.get_accel().y +
                         this->imu.get_accel().z) /
                        3;
      if (!(std::abs(avg_speed) < 0.5)) {
        zero_time = false;
      }
    } else if (this->current_pid_state == fire::drive::pid_state::Turn) {
      if (!zero_time) {
        zero_start = pros::millis();
      } else if (pros::millis() > zero_start + this->turn_zero_timeout) {
        break;
      }

      if (!large_time) {
        large_start = pros::millis();
      } else if (pros::millis() > large_start + this->turn_large_timeout) {
        break;
      }

      if (!small_time) {
        small_start = pros::millis();
      } else if (pros::millis() > small_start + this->turn_small_timeout) {
        break;
      }

      small_time = true;
      large_time = true;
      zero_time = true;
      float deg = std::abs(this->deg_target - this->imu.get_rotation());
      if (!(deg < this->turn_small_error)) {
        small_time = false;
      }
      if (!(deg < this->turn_large_error)) {
        large_time = false;
      }
      if (!(std::abs(this->deg_prev_error) < 1)) {
        zero_time = false;
      }
    }

    pros::delay(fire::delay);
  }
  this->current_pid_state = this->None;
  this->set_tank(0, 0);
}

void fire::drive::wait_until(double target) {
  while (true) {
    if (this->current_pid_state == pid_state::Drive) { // drive wait
      bool break_out = true;

      for (int i = 0; i < this->left_drive.size(); i++) {
        if ((std::abs(right_targets[i]) -
             std::abs(this->left_drive[i].get_position())) >
            this->drive_small_error) {
          break_out = false;
          break;
        }
      }
      for (int i = 0; i < this->right_drive.size(); i++) {
        if ((std::abs(left_targets[i]) -
             std::abs(this->right_drive[i].get_position())) >
            this->drive_small_error) {
          break_out = false;
          break;
        }
      }

      if (break_out) {
        break;
      }
    } else if ((this->current_pid_state == pid_state::Turn) ||
               (this->current_pid_state ==
                pid_state::Swing)) { // swing and turn waits
      if ((std::abs(target) - std::abs(this->imu.get_rotation())) <=
          this->turn_small_error) { // within small error of the wait until
        break;                      // stop blocking
      }
    }

    pros::delay(fire::delay);
  }
}

void fire::drive::set_exit_conditions(fire::pid_types pid_type,
                                      float small_error, float large_error,
                                      int small_timeout, int large_timeout,
                                      int zero_timeout) {
  if (pid_type == fire::pid_types::Drive) {
    this->drive_small_error = small_error;
    this->drive_large_error = large_error;
    this->drive_small_timeout = small_timeout;
    this->drive_large_timeout = large_timeout;
    this->drive_zero_timeout = zero_timeout;
  } else if (pid_type == fire::pid_types::Turn) {
    this->turn_small_error = small_error;
    this->turn_large_error = large_error;
    this->turn_small_timeout = small_timeout;
    this->turn_large_timeout = large_timeout;
    this->turn_zero_timeout = zero_timeout;
  } else if (pid_type == fire::pid_types::Swing) {
    this->swing_small_error = small_error;
    this->swing_large_error = large_error;
    this->swing_small_timeout = small_timeout;
    this->swing_large_timeout = large_timeout;
    this->swing_zero_timeout = zero_timeout;
  }
}

void fire::drive::set_pid(fire::pid_types pid_type, float kp, float ki,
                          float kd) {
  if (pid_type == fire::pid_types::Drive) {
    this->drive_Kp = kp;
    this->drive_Ki = ki;
    this->drive_Kd = kd;
  } else if (pid_type == fire::pid_types::Turn) {
    this->turn_Kp = kp;
    this->turn_Ki = ki;
    this->turn_Kd = kd;
  }
}

void fire::drive::set_drive_pid(float distance, int speed) {
  this->current_pid_state = pid_state::None;
  this->start_deg = this->imu.get_rotation();

  // set left motor targets
  for (int i = 0; i < this->left_drive.size(); i++) {
    this->left_drive[i].tare_position();
    float start = left_drive[i].get_position();
    float target =
        (distance / (this->diameter * 3.14)) * (float(200) / this->rpm);
    if (left_drive[i].is_reversed()) {
      target = start - target;
    } else {
      target = start + target;
    }
    this->left_targets[i] = target;
    this->left_total_error[i] = 0.0;
    this->left_prev_errors[i] = 0.0;
  }

  // set right motor targets
  for (int i = 0; i < this->right_drive.size(); i++) {
    this->right_drive[i].tare_position();
    float start = right_drive[i].get_position();
    float target =
        (distance / (this->diameter * 3.14)) * (float(200) / this->rpm);
    if (right_drive[i].is_reversed()) {
      target = start + target;
    } else {
      target = start - target;
    }
    this->right_targets[i] = target;
    this->right_total_error[i] = 0.0;
    this->right_prev_errors[i] = 0.0;
  }

  this->speed = speed;
  this->current_pid_state = pid_state::Drive;
}

void fire::drive::set_turn_pid(float deg, int speed) {
  this->current_pid_state = pid_state::None;

  this->deg_target = deg;
  this->deg_prev_error = 0.0;
  this->deg_total_error = 0.0;

  this->speed = speed;
  this->current_pid_state = pid_state::Turn;
}

void fire::drive::set_tank(int left, int right) {
  for (int i = 0; i < this->left_drive.size(); i++) {
    left_drive[i] = left;
  }
  for (int i = 0; i < this->right_drive.size(); i++) {
    right_drive[i] = right;
  }
}

// active breaking mode
void fire::drive::set_active_breaking(float kp) {
  this->active_breaking_kp = kp;
}

void fire::drive::init_active_breaking() {
  pros::Task(this->active_breaking_task, (void *)this, TASK_PRIORITY_DEFAULT,
             TASK_STACK_DEPTH_DEFAULT, "Active Breaking Task");
}

void fire::drive::active_breaking_task(void *c) {
  while (true) {
    if (!(pros::competition::is_autonomous() ||
          pros::competition::is_disabled())) {
      if (std::abs(fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)) !=
              0 ||
          std::abs(fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) !=
              0 ||
          std::abs(fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) !=
              0 ||
          std::abs(fire::cont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) !=
              0) {
        fire::lcd::println(2, "Setting active break");
        ((fire::drive *)c)
            ->set_pid(fire::pid_types::Drive,
                      ((fire::drive *)c)->active_breaking_kp, 0.0, 0.0);
        ((fire::drive *)c)->set_drive_pid(0, 127);
        ((fire::drive *)c)->current_pid_state = fire::drive::None;
      } else {
        fire::lcd::println(2, "Using active break");
        ((fire::drive *)c)->current_pid_state = fire::drive::Drive;
      }
    }
    pros::delay(fire::delay);
  }
}

// calibrate imu
void fire::drive::calibrate_imu() {
  if (pros::c::get_plugged_type(this->imu.get_port()) == 6) {
    fire::lcd::print("Calabrating IMU...");
    this->imu.reset(true);
    fire::lcd::print("IMU Calabrated.");
  } else {
    fire::lcd::print("IMU not detected on port " +
                     std::to_string(this->imu.get_port()));
  }
}
