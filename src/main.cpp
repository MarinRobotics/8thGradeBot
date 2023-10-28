#include "main.h"
#include "pros/misc.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {

	pros::lcd::initialize();
	pros::lcd::set_text(1, "we did it");
    pros::lcd::initialize();

	pros::delay(100);	
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
float power_multiplier = 0.75;
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_front(4);
	pros::Motor left_back(3);
	pros::Motor right_front(2, true);
	pros::Motor right_back(1, true);
	pros::Motor arm(5);
	pros::Motor left_sweeper(6);
	pros::Motor right_sweeper(7);
	pros::Motor left_wall(8);
	pros::Motor right_wall(9);   

	pros::Motor wallright(8);
	pros::Motor wallleft(9);

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
	{
		wallright.move_absolute(75,110);
		wallleft.move_absolute(75,110);
		pros::lcd::print(5, "wall up");
		pros::delay(20);
	}


	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
	{
		wallright.move_absolute(0,35);
		wallleft.move_absolute(0,35);
		pros::lcd::print(5, "wall down");
		pros::delay(20);
	}

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
	{
		wallright.move_absolute(50,110);					
		wallleft.move_absolute(50,110);
		pros::lcd::print(5, "wall up");
		pros::delay(20);
	}

	int right_power = master.get_analog(ANALOG_RIGHT_Y);
	int left_power = master.get_analog(ANALOG_LEFT_Y);

	right_front = right_power;
	right_back = right_power;
	left_front = left_power;
	left_back = left_power;

	int arm_power = 100;

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		arm = arm_power;
	} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		arm = -arm_power;
	} else {
		arm = 0;
	}

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			
	}
}