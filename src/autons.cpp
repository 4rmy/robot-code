#include "autons.h"
#include "bot.h"

const int DRIVE_SPEED = 110;
const int TURN_SPEED = 80;
const int SWING_SPEED = 80;

void set_exit_conditions() {
  chassis.set_pid(fire::pid_types::Drive, 1.5, 0.0, 10.0);
  chassis.set_pid(fire::pid_types::Turn, 0.05, 0.0, 0.5);

  chassis.set_exit_conditions(fire::pid_types::Drive, 1, 4, 50, 100, 500);
  chassis.set_exit_conditions(fire::pid_types::Turn, 7, 10, 50, 100, 500);
  chassis.set_exit_conditions(fire::pid_types::Swing, 0.5, 3, 150, 350, 500);
}

void close_qual() {
  intake = 127;

  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();
  chassis.set_tank(-100, -100);
  pros::delay(300);

  chassis.set_drive_pid(16, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  right_wing.set_value(true);
  pros::delay(200);

  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();

  right_wing.set_value(false);
  pros::delay(200);

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-235, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-34.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-205, TURN_SPEED);
  chassis.wait_drive();

  pros::delay(500);

  right_wing.set_value(true);

  /*

  right_wing.set_value(true);*/
}
void close_intercept() {
  intake = 127;
  right_wing.set_value(true);
  pros::delay(100);
  right_wing.set_value(false);

  chassis.set_drive_pid(48, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  intake = 63;

  chassis.set_drive_pid(-48, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(20, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  left_wing.set_value(true);
  pros::delay(150);

  chassis.set_turn_pid(-120, TURN_SPEED);
  chassis.wait_drive();

  left_wing.set_value(false);

  chassis.set_turn_pid(110, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(38, DRIVE_SPEED);
  chassis.wait_until(6);
  intake = -127;
  chassis.wait_drive();

  chassis.set_turn_pid(60, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();
}
void close_block() {
  intake = 127;
  chassis.set_drive_pid(48, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(85, TURN_SPEED);
  chassis.wait_drive();

  left_wing.set_value(true);

  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();
}

void far_qual() {
  intake = 127;
  pros::delay(500);

  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;

  left_wing.set_value(true);

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-110, TURN_SPEED);
  chassis.wait_drive();

  left_wing.set_value(false);

  chassis.set_turn_pid(-65, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();
  chassis.set_tank(-100, -100);
  pros::delay(800);

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.stop_pid();
  chassis.set_tank(100, 100);
  pros::delay(400);

  intake = 0;

  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-60, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(210, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();

  pros::delay(200);

  right_wing.set_value(true);
}
void far_five() {
  intake = 127;
  right_wing.set_value(true);
  pros::delay(300);
  right_wing.set_value(false);

  chassis.set_drive_pid(52, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-26, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  intake = -127; 
  pros::delay(400);

  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;

  chassis.set_drive_pid(22, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-50, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-290, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.set_drive_pid(-28, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-430, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;

  chassis.set_drive_pid(32, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-34, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-440, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-475, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  left_wing.set_value(true);

  chassis.set_turn_pid(-520, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();
  chassis.set_tank(-100, -100);
  pros::delay(500);

  chassis.set_tank(0, 0);
}
void far_six() {
  intake = 127;
  pros::delay(500);

  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;

  left_wing.set_value(true);

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-110, TURN_SPEED);
  chassis.wait_drive();

  left_wing.set_value(false);

  chassis.set_turn_pid(-65, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();
  chassis.set_tank(-100, -100);
  pros::delay(800);

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.stop_pid();
  chassis.set_tank(100, 100);
  pros::delay(400);

  intake = 0;

  chassis.set_drive_pid(-17, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(15, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;

  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  intake = 127;

  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  left_wing.set_value(true);
  right_wing.set_value(true);

  chassis.stop_pid();
  chassis.set_tank(-100, -100);
  pros::delay(800);

  left_wing.set_value(true);
  right_wing.set_value(true);

  chassis.set_drive_pid(8, 127);
  chassis.wait_drive();

  intake = -127;

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();

  chassis.stop_pid();
  chassis.set_tank(127, 127);
  pros::delay(800);
}

/*
void test_auton() {
    fire::lcd::print("Auton Started");

    fire::lcd::print("Driving Forward");
    chassis.set_drive_pid(24, DRIVE_SPEED);
    chassis.wait_until(12);
    // do something after 12 inches
    chassis.wait_drive();

    fire::lcd::print("Driving Backwards");
    chassis.set_drive_pid(-24, DRIVE_SPEED);
    chassis.wait_drive();

    fire::lcd::print("Turning Right");
    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();

    fire::lcd::print("Turning Left");
    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();

    fire::lcd::print("Straightning");
    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();



    fire::lcd::print("Auton Finished");
    fire::cont.rumble(".");
}
*/