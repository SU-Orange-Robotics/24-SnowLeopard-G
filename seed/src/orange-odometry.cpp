#include "../include/orange-odometry.h"

// ============== EXPERIMENTAL STUFF ==============
OrangeOdometry::OrangeOdometry(inertial* inertialSensor, gps* gpsSensor, mode newMode = defaultMode) 
  : imu(inertialSensor), gpsSensor(gpsSensor), odomMode(newMode)
{
  currentHeading = 0;
}

void OrangeOdometry::resetHeading() {
  currentHeading = 0;
}

void OrangeOdometry::getIMUHeading() {
  currentHeading = imu->heading();
}

void OrangeOdometry::printLocation() {

  Brain.Screen.setCursor(1, 1);
  // brain.Screen.print("X: %f", x);
  // brain.Screen.setCursor(2, 1);
  // brain.Screen.print("Y: %f", y);
  // brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Heading: %f", currentHeading);
}