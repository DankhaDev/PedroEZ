#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 12, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.75, 0, 6.2, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 1.67, 0, 6.2, 0);
  chassis.set_pid_constants(&chassis.turnPID, 8, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();


  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void leftAuton() {
  //turn to face 2 degrees with PID
  chassis.set_turn_pid(2, TURN_SPEED);
  chassis.wait_drive();

  //drive forward 54 inches with PID
  chassis.set_drive_pid(54, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //intakeOut()
  intakeOut();

  //drive forward 6 inches with PID
  chassis.set_drive_pid(6, DRIVE_SPEED, true);
  chassis.wait_drive();

  //drive reverse 6 inches with PID
  chassis.set_drive_pid(-6, DRIVE_SPEED, true);
  chassis.wait_drive();

  //intakeStop()
  intakeStop();

  //turn to face 90 degrees with PID
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  //openLeftWing()
  openLeftWing();

  //drive forward 34 inches with PID
  chassis.set_drive_pid(34, DRIVE_SPEED, true);
  chassis.wait_drive();

  //drive reverse 4 inches with PID
  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();

  //closeLeftWing()
  closeLeftWing();

  //turn to face 230 degrees with PID
  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  //drive 67 inches forward with PID
  chassis.set_drive_pid(67, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 130 degrees with PID
  chassis.set_turn_pid(130, TURN_SPEED);
  chassis.wait_drive();

  //openRightWing()
  openRightWing();

  //drive forward 17 inches with PID
  chassis.set_drive_pid(17, DRIVE_SPEED, true);
  chassis.wait_drive();

  //intakeOut()
  intakeOut();

  //turn to face 80 degrees with PID
  chassis.set_turn_pid(80, TURN_SPEED);
  chassis.wait_drive();

  //openWings()
  openWings();

  //drive forward 38 inches with PID
  chassis.set_drive_pid(38, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 100 degrees with PID
  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();
}

void rightAuton() {
  chassis.set_drive_pid(48, DRIVE_SPEED, true); //drive forward 4 feet with PID
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED); //turn to face 90 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(6, DRIVE_SPEED, true); //drive forward 0.5 feet with PID
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED, true); //drive reverse 0.5 feet with PID
  chassis.wait_drive();

  chassis.set_turn_pid(30, TURN_SPEED); //turn to face 30 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(-36, DRIVE_SPEED, true); //drive in reverse 3 feet with PID
  chassis.wait_drive();

  openWings(); //open wings

  chassis.set_swing_pid(ez::RIGHT_SWING, 180, SWING_SPEED); //swing to the right 180 degrees using PID
  chassis.wait_drive();

  chassis.set_drive_pid(-42, DRIVE_SPEED, true); //drive 3.5 feet in reverse with PID
  chassis.wait_drive();

  chassis.set_drive_pid(6, DRIVE_SPEED, true); //drive .5 feet forward with PID
  chassis.wait_drive();

  chassis.set_turn_pid(300, TURN_SPEED); //turn to face 300 degrees with PID
  chassis.wait_drive();

  intakeIn(); //intake in

  chassis.set_drive_pid(36, DRIVE_SPEED, true); //drive forward 3 feet with PID
  chassis.wait_drive();

  intakeOut(); //intake out

  chassis.set_drive_pid(-6, DRIVE_SPEED, true); //drive reverse .5 feet with PID
  chassis.wait_drive();

  chassis.set_turn_pid(105, TURN_SPEED); //turn to face 105 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(36, DRIVE_SPEED, true); //drive forward 3 feet
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED); //turn to face 90 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(3, DRIVE_SPEED, true); //drive forward 3 inches using PID
  chassis.wait_drive();

  chassis.set_turn_pid(130, TURN_SPEED); //turn to face 130 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(-60, DRIVE_SPEED, true); //drive reverse 5 feet with PID
  chassis.wait_drive();

  openWings(); //open wings

  chassis.set_turn_pid(180, TURN_SPEED); //turn to face 180 degrees with PID
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED, true); //drive reverse .5 feet with PID
  chassis.wait_drive();
}

void skillsAuton() {

  //open wings
  openWings();

  //turn to face 45 degrees with PID
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse 2 feet with PID
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 0 degrees with PID
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse .5 feet with PID
  chassis.set_drive_pid(-6, DRIVE_SPEED, true);
  chassis.wait_drive();

  //close wings
  closeWings();

  //drive forward 2 feet with PID
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 320 degrees with PID
  chassis.set_turn_pid(320, TURN_SPEED);
  chassis.wait_drive();

  //kickerOn
  kickerOn();
  //wait 40 seconds
  pros::delay(40000);
  //kickerOff
  kickerOff();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse 8 feet with PID
  chassis.set_drive_pid(-96, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 330 degrees with PID
  chassis.set_turn_pid(330, TURN_SPEED);
  chassis.wait_drive();

  //open wings
  openWings();

  //drive reverse 2 feet with PID
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //close wings
  closeWings();

  //drive forward 3 inches with PID
  chassis.set_drive_pid(3, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //drive forward 2 feet with PID
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 315 degrees with PID
  chassis.set_turn_pid(315, TURN_SPEED);
  chassis.wait_drive();

  //open wings
  openWings();

  //drive 2 feet forward with PID
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //close wings
  closeWings();

  //drive reverse 3 inches with PID
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  //drive forward 2 feet with PID
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 315 degrees with PID
  chassis.set_turn_pid(315, TURN_SPEED);
  chassis.wait_drive();

  //open wings
  openWings();

  //drive 2 feet forward with PID
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse 3 inches with PID
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();

  //close wings
  closeWings();

  //drive forward 3 inches with PID
  chassis.set_drive_pid(3, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 230 degrees with PID
  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  //drive forward 3 feet with PID
  chassis.set_drive_pid(36, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees with PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //open wings
  openWings();

  //drive reverse 2 feet with PID
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 220 degrees with PID
  chassis.set_turn_pid(220, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse 9 inches with PID
  chassis.set_drive_pid(-9, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 180 degrees with PID
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  //drive reverse 3 inches with PID
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void soloAWP() {
  //drive reverse 3 feet at 50% speed using PID
  chassis.set_drive_pid(-36, DRIVE_SPEED * 0.5, true);
  chassis.wait_drive();

  //turn to face 270 degrees at 50% speed using PID
  chassis.set_turn_pid(270, TURN_SPEED * 0.5);
  chassis.wait_drive();

  //drive in reverse 1.3 feet at 50% speed using PID
  chassis.set_drive_pid(-15.6, DRIVE_SPEED * 0.5, true);
  chassis.wait_drive();

  //fire kicker
  kickerHit();

  //drive forward .5 feet at normal speed using PID
  chassis.set_drive_pid(6, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 120 degrees at normal speed using PID
  chassis.set_turn_pid(120, TURN_SPEED);
  chassis.wait_drive();

  //drive in reverse for 4 feet at normal speed using PID
  chassis.set_drive_pid(-48, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 230 degrees at normal speed using PID
  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  //open wings
  openWings();

  //drive reverse 1.5 feet at normal speed using PID
  chassis.set_drive_pid(-18, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turn to face 270 degrees at normal speed using PID
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  //close wings
  closeWings();

  //drive in reverse 4 feet
  chassis.set_drive_pid(-48, DRIVE_SPEED, true);
  chassis.wait_drive();

  //open right wing
  openRightWing();
}