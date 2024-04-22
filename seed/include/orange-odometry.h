#pragma once

#include "vex.h"
#include "robot-config.h"

// Odometry class
// ============== EXPERIMENTAL STUFF ==============
// Potentially fusing multiple sensor units to give more accurate odometry

// define three modes in enum, inertial only, gps only, and inertial + gps
enum mode { IMU_ONLY, GPS_ONLY, FUSION };

const mode defaultMode = IMU_ONLY;

struct location {
  double x;
  double y;
  double heading;
};

class OrangeOdometry {
public:

  OrangeOdometry(inertial* inertialSensor, gps* gpsSensor, mode newMode); // either could be null

  void resetHeading();

  void getIMUHeading();

  void printLocation();

private:
  double currentHeading;

  // reference to inertial sensor

  mode odomMode;
  vex::inertial* imu;
  vex::gps* gpsSensor;
};
