#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-14, -15, 16}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{11, 12, -13}

  // IMU Port
  ,20

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.67

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

//Auton Selectors
pros::ADIDigitalIn increase('A');
pros::ADIDigitalIn decrease('B');

//Kicker
pros::Motor kicker(17);
pros::Optical kickerOptical(18);
pros::Rotation kickerRotation(19);

//Intake
pros::Motor intake(1);


//Wings
pros::ADIPort leftWing('C', pros::E_ADI_DIGITAL_OUT);
pros::ADIPort rightWing('D', pros::E_ADI_DIGITAL_OUT);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    //Default Autons, good for PID tuning
    
    // Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
    
    
    /*
    //Competition Autons
    Auton("Left Auton\n\nScore alliance triball\nHit matchload zone triball out of the corner\nPush 2 green triballs\nTouch elevation bar from the outside with wings\nHalf AWP", leftAuton),
    Auton("Right Auton\n\nScore 2 green triballs\nScore alliance triball\nGrab and score 3rd green triball\nTouch elecation bar from the outside\nHalf AWP", rightAuton),
    Auton("Skills Auton\n\n Auton for skills, shocker", skillsAuton),
    Auton("Solo AWP Auton\n\nScore alliance triball\nHit matchload zone triball out of the corner\nTouch elevation bar from inside\nFull Solo AWP", soloAWP),
    */  
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  //Change the auton selector to use buttons for forward and back instead of the screen
  // ez::as::limit_switch_lcd_initialize(&increase, &decrease);
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



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
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}

//opens both wings
void openWings() { 
  leftWing.set_value(true);
  rightWing.set_value(true);
}
void openLeftWing() { //Open only the left wing
  leftWing.set_value(true);
}
void openRightWing() { //Open only the right wing
  rightWing.set_value(true);
}

//closes both wings
void closeWings() { 
  leftWing.set_value(false);
  rightWing.set_value(false);
}
void closeLeftWing() { //Close only the left wing
  leftWing.set_value(false);
}
void closeRightWing() { //Close only the right wing
  rightWing.set_value(false);
}

void intakeIn() {
  intake.move_velocity(600); // Spin the intake inward at full speed
}

void intakeOut() {
  intake.move_velocity(-600); // Spin the intake outward at full speed
}

void intakeStop() {
  intake.move_velocity(0); // Stop the intake
}

void kickerHit() {
  kicker.move_velocity(-100); // Spin the kicker in reverse at full speed
  pros::delay(1000); // Wait for 1 second
  kicker.move_velocity(0); // Stop the kicker
}

void kickerOn() {
  kicker.move_velocity(-100); //spin motor in reverse
}

void kickerOff() {
  kicker.move_velocity(0); //stop the kicker
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

// State of the wing's toggle
bool pneumaticsExtended = false;

void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

double kickerTarget = 420; // This is the target position in degrees
double kickerErrorThreshold = 5; // Set this to the acceptable error range
double kickerError = 0;

  while (true) {
    // chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
    
    double kickerCurrent = kickerRotation.get_position() / 100;
    double kickerError = kickerTarget - kickerCurrent;

// Bang-bang control loop
if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    // Get the hue from the optical sensor
    int hue = kickerOptical.get_hue();

    // Check if the hue is within the specified range
    if (hue >= 112 && hue <= 117) {
        kickerOn(); // Fire the kicker
    } else if (kickerError > kickerErrorThreshold) { // If the current position is less than the target
        kickerOn(); // Move the kicker in reverse at full speed
    } else if (kickerError < -kickerErrorThreshold) { // If the current position is greater than the target
        kickerOn(); // Move the kicker reverse at full speed
    } else {
        kickerOff(); // Stop the kicker
    }
}

// Fire the kicker when L2 is being held
if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    kickerOn();
  } 



    // Intake spins inward when R2 is held
    // Intake spins outward when R1 is held
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intakeIn(); // Spin the intake forward at full speed
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intakeOut(); // Spin the intake in reverse at full speed
    } else {
      intakeStop(); // Stop the intake
    }

    // Wing Toggle
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      pneumaticsExtended = !pneumaticsExtended;
        if (pneumaticsExtended) {
        openWings();
        } else {
        closeWings();
        }
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
