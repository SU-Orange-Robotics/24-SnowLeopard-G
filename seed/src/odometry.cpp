#include "odometry.h"

void Odometry::resetHeading() {
  currentHeading = 0;
}

void Odometry::getIMUHeading() {
  currentHeading = inertialSensor.heading();
}