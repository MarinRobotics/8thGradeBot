#include "main.h"
#include "pros/misc.h"
#define M_PI 3.14159265358979323846 /* pi */

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(5, "I was pressed!");
	}
	else
	{
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
	pros::lcd::set_text(1, "autono");

	pros::Motor left_sweeper_initializer(6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_sweeper_initializer(7, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor wallright_initializer(8, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wallleft_initializer(9, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_front_initializer(10, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

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

float inchesToRotations(float inches)
{
	return inches / (2 * M_PI * 2);
}
float inchesToDegrees(float inches)
{
	return inchesToRotations(inches) * 360.0;
}
/*
	drivetrain.turnFor(left, -45, degrees);
	drivetrain.driveFor(reverse, -700, mm);
	drivetrain.turnFor(right, -45, degrees);
	drivetrain.driveFor(reverse, -175, mm);
	drivetrain.driveFor(forward, -200, mm);
	drivetrain.turnFor(right, 45, degrees);
	drivetrain.driveFor(reverse, 700, mm);
	drivetrain.turnFor(right, 45, degrees);
	drivetrain.driveFor(reverse, 500, mm);
	drivetrain.turnFor(right, 30, degrees, false);
*/
const float ROBOT_DISTANCE_PER_DEGREE = (10.25 * M_PI) / 360;
void turn(pros::Motor_Group &left, pros::Motor_Group &right, float robot_turn_degrees)
{
	std::vector<std::int32_t> start_draw = left.get_current_draws();
	// use motor
	float robot_turn_distance = ROBOT_DISTANCE_PER_DEGREE * robot_turn_degrees;
	float motor_turn_degrees = inchesToDegrees(robot_turn_distance * 1.08);
	left.move_relative(motor_turn_degrees, 100);
	std::vector<double> start_pos = left.get_target_positions();
	right.move_relative(-motor_turn_degrees, 100);

	while (true)
	{
		pros::delay(10);
		std::vector<double> current_draw = left.get_positions();
		float delta = fabs(current_draw[0] - start_pos[0]);
		std::cout << "current delta" << delta << "\n";
		if (delta < 5)
		{
			break;
		}
	}
}
void move(pros::Motor_Group &motors, float distance)
{
	// get current draws
	// use motor
	motors.move_relative(inchesToDegrees(distance), 100);
	std::vector<double> start_pos = motors.get_target_positions();
	// loop until current draws are close to get
	while (true)
	{
		pros::delay(10);
		std::vector<double> current_draw = motors.get_positions();
		float delta = fabs(current_draw[0] - start_pos[0]);
		std::cout << "current delta" << delta << "\n";
		if (delta < 5)
		{
			break;
		}
	}
}

void autonomous()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor left_front(4, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_back(3, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_front(2, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_back(1, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor arm(5, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor_Group funny({
		left_front,
		left_back,
		right_front,
		right_back,
	});
	pros::Motor_Group funny_left({
		left_front,
		left_back,
	});
	pros::Motor_Group funny_right({
		right_front,
		right_back,
	});

	pros::Motor_Group arm_fun({
		arm
	});
	
	

	move(funny, -50);
	turn(funny_left, funny_right, 30);
	turn(funny_left, funny_right, 30);
	turn(funny_left, funny_right, 30);
	pros::delay(50);
	//move(funny, 6);
	//turn(funny_left, funny_right, 180);
	//move(funny, 15);
	move(funny, -6.5);
	move(funny, 14);
	turn(funny_left, funny_right, 180);
	pros::delay(20);
	turn(funny_left, funny_right, -55);
	move(funny, -30);
	move(arm_fun, 30);
	//move(funny, -29);
	

	//turn(funny_left, funny_right, -90);
	//turn(funny_left, funny_right, 90);
	//move(funny, 12.56);
	//turn(funny_left, funny_right, 180);
	//move(funny, 12.56);
	//move(funny, -12.56);

	/*10.25

	turn(funny_left, funny_right, -45);


	funny.move_absolute(inchesToDegrees(27.56), 100);
	drivetrain.turnFor(right, -45, degrees);
	funny.move_absolute(inchesToDegrees(-6.89), 100);
	funny.move_absolute(inchesToDegrees(7.87), 100);
	drivetrain.turnFor(right, 45, degrees);
	funny.move_absolute(inchesToDegrees(-27.56), 100);
	drivetrain.turnFor(right, 45, degrees);
	funny.move_absolute(inchesToDegrees(-19.7), 100);
	drivetrain.turnFor(right, 30, degrees, false);
*/
}

bool myPrint(int16_t line, const char *fmt)
{
	pros::lcd::print(line, fmt);
	pros::delay(20);
}

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

float power_multiplier = 1.5;

void opcontrol()
{
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
	arm.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
	bool toggle = false;

	// myPrint(3, "starting");
	pros::lcd::print(2, "starting");
	// pros::delay(20);
	while (true)
	{
		/*
				if (toggle)
				{
					right_sweeper.move_absolute(0, 100);

				}
				else
				{
					right_sweeper.move_absolute(0, 100);

				}

				if ( master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
				{
					if (!latch)
					{ // if latch is false, flip toggle one time and set latch to true
						toggle = !toggle;
						latch = true;
					}
				}
				else
				{
					latch = false; // once button is released then release the latch too
				}
		*/
		int arm_power = 100;

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
		{
			toggle = !toggle;
			if (toggle)
			{
				right_sweeper.move_absolute(75, 115);
				pros::lcd::print(0, "i like pizza");
			}
			else
			{
				right_sweeper.move_absolute(0, 115);
				pros::lcd::print(0, "off");
			}
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
		{
			toggle = !toggle;
			if (toggle)
			{
				left_sweeper.move_absolute(85, -115);
				pros::lcd::print(0, "i like pizza");
			}
			else
			{
				left_sweeper.move_absolute(0, 115);
				pros::lcd::print(0, "off");
			}
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			wallright.move_absolute(75, 110);
			wallleft.move_absolute(75, 110);
			pros::lcd::print(5, "wall up");
			pros::delay(20);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			wallright.move_absolute(0, 35);
			wallleft.move_absolute(0, 35);
			pros::lcd::print(5, "wall down");
			pros::delay(20);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			wallright.move_absolute(50, 110);
			wallleft.move_absolute(50, 110);
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