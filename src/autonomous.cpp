#include "autonomous.h"
#include "vex.h"
#include "robot-config.h"
#include "drive.h"
#include "intakeCat.h"
#include "../seed/include/auto-commands.h"
#include <chrono>

// declare helper functions
void driveForwardTimed(double pow, double time);
void driveCustomSpeed(double leftPow, double rightPow, double time);
void greenTurnTimed(double pow, double time);
void push_ball();
void intake_and_shoot();

/* ------------------------------------------------ */
/* ------ Actual Competition Auton goes here ------ */
/* ------------------------------------------------ */

void oneKick() {
  ballKicker.setReversed(false);
  ballKicker.spinToPosition(-190, deg, 100, velocityUnits::pct, false);
  int counter = 0;
  while (ballKicker.position(deg) > -190) {
    wait(5, msec);
    if (counter++ > 120) {
      break;
    }
  }
  
  ballKicker.spinToPosition(0, deg, 100, velocityUnits::pct, true);
}

void kickBalls(int numberOfTries, double waitTime) {
  for (int i = 0; i < numberOfTries; i++) {
    oneKick();
    wait(waitTime, sec);
  }
}

void lowerCat() {
  while (catapultRot.angle(rotationUnits::deg) > 74) {
    catapultLower(50);
    wait(5, msec);
  }
  catapultStop();
}

void goUnderSafely() {
  // driveCustomSpeed(-50, -51, 3.5);
  int counter = 0;
  while (counter++ < 340) {
    if (realHeading() < 80 || realHeading() > 100) {
      driveForwardTimed(30, 0.2);
      turnToTargetIMUOnly(drive, 40, 85);
      counter += 20;
    } else {
      drive.driveForward(-50);
    }

    wait(10, msec);
  }
}

void autonomous_head_to_head(void) {
  lowerCat();
  imu.calibrate();

  while (imu.isCalibrating()) {
    wait(100, msec);
  }

  kickBalls(1, 1.2);

  driveForwardTimed(30, 1.5);
  turnToTargetIMUOnly(drive, 40, 82);
  // driveForwardTimed(-50, 3.5);
  driveCustomSpeed(50, 51, 3.5);
  // goUnderSafely();
  driveForwardTimed(100, 0.5);
  turnToTargetIMUOnly(drive, 40, 100);

  // turn
  driveCustomSpeed(60, 50, 1.5);

  // push in 1st time
  // driveForwardTimed(-100, 1.8);
  driveCustomSpeed(100, 90, 1.8);

  driveForwardTimed(50, 0.6);

  // scoop balls next to the wllas
  turnToTargetIMUOnly(drive, 40, 150);
  driveCustomSpeed(70, 50, 0.8);


  // push in 2nd time
  driveForwardTimed(100, 1.3);
  // driveCustomSpeed(-100, -90, 1.5);
  driveForwardTimed(50, 0.8);

  // scoop balls next to the walls
  turnToTargetIMUOnly(drive, 40, 150);


  // push in 3rd time
  for (int i = 0; i < 3; i++) {
    driveCustomSpeed(100, 95, 1.5);
    driveForwardTimed(50, 0.8);
    turnToTargetIMUOnly(drive, 60, 160);
  }
  drive.stop();

}

void autonomous_competition(void) {
  // IMU calibration

  lowerCat();
  imu.calibrate();

  

  while (imu.isCalibrating()) {
    wait(100, msec);
  }

  // Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("IMU Calibrated");
  kickBalls(18, 0.9);

  driveForwardTimed(-30, 1.5);
  turnToTargetIMUOnly(drive, 40, 82);
  // driveForwardTimed(-50, 3.5);
  driveCustomSpeed(-50, -51, 3.5);
  // goUnderSafely();
  driveForwardTimed(-100, 0.5);
  turnToTargetIMUOnly(drive, 40, 100);
  // driveCustomSpeed(-50, -45, 1.0);

  // turn
  driveCustomSpeed(-60, -50, 1.5);

  // push in 1st time
  // driveForwardTimed(-100, 1.8);
  driveCustomSpeed(-100, -90, 1.8);

  driveForwardTimed(50, 0.6);

  // scoop balls next to the wllas
  turnToTargetIMUOnly(drive, 40, 150);
  driveCustomSpeed(-70, -50, 0.8);


  // push in 2nd time
  driveForwardTimed(-100, 1.3);
  // driveCustomSpeed(-100, -90, 1.5);
  driveForwardTimed(50, 0.8);

  // scoop balls next to the walls
  turnToTargetIMUOnly(drive, 40, 150);


  // push in 3rd time
  // drop wings
  for (int i = 0; i < 5; i++) {
    driveCustomSpeed(-100, -95, 1.5);
    driveForwardTimed(50, 0.8);
    turnToTargetIMUOnly(drive, 60, 160);
  }
  drive.stop();
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
void driveForwardTimedSmoothly(double pow, double time) {
  // auto startTime = std::chrono::high_resolution_clock::now();

  // if (pow > 0) {
  //   for (int i = 10; i < pow; i++) {
  //     // Check elapsed time
  //     auto currentTime = std::chrono::high_resolution_clock::now();
  //     auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
      
  //     if (elapsedTime >= time) break; // Stop if the specified time has passed
      
  //     drive.driveForward(i);
  //     wait(10, msec);
  //   }
  // } else {
  //   for (int i = 10; i > pow; i--) {
  //     // Check elapsed time
  //     auto currentTime = std::chrono::high_resolution_clock::now();
  //     auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
      
  //     if (elapsedTime >= time) break; // Stop if the specified time has passed
      
  //     drive.driveForward(i);
  //     wait(10, msec);
  //   }
  // }

  // drive.stop();
}
void driveForwardTimed(double pow, double time) {
  drive.driveForward(pow);
  wait(time, sec);
  drive.stop();
}

void driveCustomSpeed(double leftPow, double rightPow, double time) {
  drive.leftDrive(leftPow);
  drive.rightDrive(rightPow);
  wait(time, sec);
  drive.stop();
}

void greenTurnTimed(double pow, double time) {
  drive.leftDrive(pow);
  drive.rightDrive(-1 * pow);
  wait(time, sec);
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
  // greenTurnToTarget(35, 30);
  
  driveForwardTimed(40, 1);

  // greenTurnToTarget(50, 315);

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