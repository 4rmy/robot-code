#include "main.h"
#include "pros/motors.hpp"

inline pros::Motor intake(1);
inline pros::Motor hang(2);

inline pros::adi::DigitalOut left_wing('b');
inline bool left_toggle = false;
inline pros::adi::DigitalOut right_wing('a');
inline bool right_toggle = false;
inline bool recent = false;