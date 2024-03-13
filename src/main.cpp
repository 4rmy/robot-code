#include "main.h"
#include "autons.h"
#include <string>
#include "bot.h"

fire::drive chassis{
  {11, 12, 13},
	{-18, -19, -20},
	17,
	600,
	1,
	2.75
};

void auton_selector_button() {
	// button to controll selector
	pros::adi::DigitalIn button('d');

	// constantly detect the button
	while (true) {
		// detect if the button is pressed down
		if (button.get_new_press()) {
			// increment the selected auton
			fire::as::page_up();
		}
		// prevent the task from freezing
		pros::delay(fire::delay);
	}
}

void initialize() {
  // set active breaking (broken rn D= )
  // chassis.set_active_breaking(10); // reccomeded to set to 0.1
  // chassis.init_active_breaking();

  // initialize the fire-lib console lcd
  fire::lcd::initialize();

  // calibrate the IMU
  chassis.calibrate_imu();

  // auton selector
  fire::as::add_autons({
      fire::as::Auton("Close Qual", close_qual),
      fire::as::Auton("Close Intercept", close_intercept),
      fire::as::Auton("Close Block", close_block),
      fire::as::Auton("Far Qual", far_qual),
      fire::as::Auton("Far Five", far_five),
      fire::as::Auton("Far Six", far_six),
  });
  fire::as::init_selector();

  // clear the display
  // fire::lcd::clear();
  fire::cont.rumble(".");

  // auton selector button; uncomment to enable an adi controlled auton selector
  // pros::Task(auton_selector_button, TASK_PRIORITY_DEFAULT,
  // TASK_STACK_DEPTH_DEFAULT, "Auton Selector Button");
}

void disabled() {
	// stop pid from attempting to run
	chassis.current_pid_state = fire::drive::None;
}

void competition_initialize() {}

void autonomous() {
  //fire::as::set_visible(false);
  // necessary if you are using pid loops for accurate movements
  chassis.init_pids();
  // make auton more consistant
  chassis.set_break_mode(pros::v5::MotorBrake::hold);
  // initialize exit conditions for autonomous
  set_exit_conditions();

  // run the auton
  //fire::as::call_selected_auton();
  far_five();
}

void opcontrol() {
  fire::as::set_visible(false);
  chassis.current_pid_state = fire::drive::None;

  // fire::lcd::clear();
  chassis.set_break_mode(pros::v5::MotorBrake::coast);
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  while (true) {
    // drive controlls; uncomment the ONE that you are using
    // chassis.tank_control();
    chassis.split_arcade();
    // chassis.split_arcade_flipped();

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intake = 127;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake = -127;
    } else {
      intake = 0;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      hang = -127;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      hang = 127;
    } else {
      hang = 0;
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      left_toggle = !left_toggle;
      recent = left_toggle;
      left_wing.set_value(left_toggle);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      right_toggle = !right_toggle;
      recent = right_toggle;
      right_wing.set_value(right_toggle);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      recent = !recent;
      right_wing.set_value(recent);
      left_wing.set_value(recent);
    }

    // delay to fix brain freezing
    pros::delay(fire::delay);
  }
}
