#include "main.h"

// Initialize the controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Set up the Drivetrain Motor Groups
// Ports: 1 (Back Left), 2 (Front Left)
pros::MotorGroup left_mg({1, 2});

// Ports: 12 (Back Right), 13 (Front Right) - Reversed
pros::MotorGroup right_mg({-12, -13});

// Set up the new auxiliary motors (e.g., intake, lift)
pros::Motor motor_8(8);
pros::Motor motor_6(6);

/**
 * Runs the operator control code.
 */
void opcontrol() {
    while (true) {
        // --- DRIVETRAIN CONTROL (Tank Drive) ---
        int left_power = master.get_analog(ANALOG_LEFT_Y);
        int right_power = master.get_analog(ANALOG_RIGHT_Y);

        left_mg.move(left_power);
        right_mg.move(right_power);

        // --- MOTOR 8 CONTROL (R1 = Forward, R2 = Backward) ---
        if (master.get_digital(DIGITAL_R1)) {
            motor_8.move(127);  // 127 is maximum forward voltage
        } else if (master.get_digital(DIGITAL_R2)) {
            motor_8.move(-127); // -127 is maximum backward voltage
        } else {
            motor_8.move(0);    // Stop if neither button is pressed
        }

        // --- MOTOR 9 CONTROL (L1 = Forward, L2 = Backward) ---
        if (master.get_digital(DIGITAL_L1)) {
            motor_6.move(127);  
        } else if (master.get_digital(DIGITAL_L2)) {
            motor_6.move(-127); 
        } else {
            motor_6.move(0);    
        }

        // Required delay to prevent the while loop from hogging CPU resources
        pros::delay(20);
    }
}