#pragma once

#include "vex.h"

// Odometry class
// Potentially fusing multiple sensor units to give more accurate odometry

class Odometry {

public:
  void resetHeading();
  void getIMUHeading();

private:
  double currentHeading;
  // reference to inertial sensor
  inertial inertialSensor;
};
