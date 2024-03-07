#include "autonomous.h"
#include "vex.h"
#include "robot-config.h"
#include "drive.h"
#include "intakeCat.h"

/* ------------------------------------------------ */
/* ------ Actual Competition Auton goes here ------ */
/* ------------------------------------------------ */
void autonomous_competition(void) {
    green_skills_auto();
}

void greenReleaseIntake() {
    // lower cat
    catapultLower();
    wait(0.6, sec);
    catapultStop();

    // free intake
    drive.driveForward(80);
    wait(0.2, sec);
    drive.stop();

    drive.driveForward(-100);
    wait(0.6, sec);
    drive.stop();

    drive.driveForward(80);
    wait(0.2, sec);
    drive.stop();
}

// ========== some helper functions & sub-routines ==========
void driveForwardTimed(double pow, double time) {
  drive.driveForward(pow);
  wait(time, sec);
  drive.stop();
}

void greenTurnTimed(double pow, double time) {
  drive.leftDrive(pow);
  drive.rightDrive(-1 * pow);
  wait(time, sec);
  drive.stop();
}

void greenTurnToTarget(bool right, double pow, double target) {
  double error = target - IMU.heading();

  if (error < 0) {
    error += 360;
  }

  double p = 1.4;

  double integral_error = 0;

  while (true) {
    error = target - IMU.heading();
    integral_error += error;
  
    if (error/50 >= 1 || integral_error >= 100) {
      pow = pow * 1 * p;
    } else {
      pow = pow * (error/50) * p;
    }

    if (right) {
      drive.leftDrive(pow);
      drive.rightDrive(-1 * pow);
    } else {
      drive.leftDrive(-1 * pow);
      drive.rightDrive(pow);
    }

    if (error < 3) {
      break;
    }

    wait(10, msec);
  }

  //stop bot
  drive.stop();
}


void push_ball() {
  int i;
  for (i = 0; i < 2; i++) {
    drive.driveForward(-80);
    wait(0.7, sec);
    drive.stop();

    wait(0.2, sec);

    drive.driveForward(60);
    wait(0.5, sec);
    drive.stop();
  }
}

void intake_and_shoot() {

  for (int i = 0; i < 10; i++) {
    if (!catInPosArmed()) {
      catapultArm();
    }

    // turn on intake
    intakeSpin(true);

    // move forward
    driveForwardTimed(60, 1.5);

    wait(0.7, sec);

    // check if ball in
    if (colorSensor.isNearObject()) {
      // shoot
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("SHOOTING");
      
      driveForwardTimed(-70, 1.1);
      for(int j =0; j < 2; j++) {
        catapultLaunch();
        // these two lines here are what does the automatic arming of the catapult.
        waitUntil(getCatAccel() <= 0.1); // <-- might be blocking, which isnt desirable
        catapultArm();
      }

      wait(0.2, sec);

    } else {
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("not shooting");
      Controller1.Screen.print(colorSensor.hue());

      wait(0.5, sec);

      continue;
    }

    // drive back
    driveForwardTimed(-50, 0.1);
    wait(0.2, sec);
  }
}

// ========== retired autonomous routines ==========
void green_skills_auto() {
  catapultLower();
  wait(0.6, sec);
  catapultStop();

  // push ball in, try three times
  push_ball();

  if (!catInPosArmed()) {
    catapultArm();
  }
  if (!catInPosArmed()) {
    catapultArm();
  }
  // turn right to 55
  greenTurnToTarget(true, 35, 30);
  
  driveForwardTimed(40, 1);

  greenTurnToTarget(false, 50, 315);

  driveForwardTimed(40, 0.7);

  // intake and shoot
  intake_and_shoot();
}

void green_autonomous() {
  
  greenReleaseIntake();


  catapultLower();
  wait(0.6, sec);
  catapultStop();
}

void autonomous_old(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // catap
  /*
  drive.driveForward(100);
  wait(0.6, sec);
  drive.stop();
  wait(1, sec);

  //drive.goToPointPID(0, 1000);
  */
  //drive.turnAndDrivePID(0, 1000);
  
  /*
  drive.turnPID(0);

  wait(1, sec);

  drive.turnPID(M_PI);

  wait(1, sec);

  drive.turnPID(M_PI / 2);

  wait(1, sec);

  drive.turnPID(5 * M_PI / 6);*/


  // drive.driveForward(-100);
  // wait(650, msec);
  // drive.stop();

  // //catapultArm();

  // drive.turnPID((-1 * M_PI / 4) + 0.0);
  // drive.driveForward(100);
  // wait(800, msec);
  // drive.stop();

  // intakeSpin();

  // int i;
  // for (i = 0; i < 6; i++) {
  //   //reverse away from bar for match load
  //   drive.driveForward(-100);
  //   wait(400, msec);
  //   drive.stop();

  //   catapultLaunch();
  //   wait(500, msec);
  //   catapultArm();

  //   // give time for match load to be loaded (in addition to catapult arm time) and allow for 
  //   drive.turnPID((-1 * M_PI / 4) + 0.0);
  //   wait(500, msec);

  //   //drive forward into bar
  //   drive.driveForward(100);
  //   wait(480, msec);
  //   drive.stop();

  //   //give time for ball to get into catapult
  //   wait(300, msec);
  // }
  // catapultLaunch();
  
  // drive.driveForward(100);

  // green_autonomous();
  green_skills_auto();
}