// #include "orange-motor.h" # for some reason even after changing makefile this doesn't work
#include "../include/orange-motor.h"

namespace orange {
  void Motor::spin(vex::directionType dir, double velocity, vex::percentUnits units) {
    limitCurrent(velocity);
    vex::motor::spin(dir, velocity, units);  // Call the base class spin
  }
  void Motor::stop(vex::brakeType mode) {
    limitCurrent(0);
    vex::motor::stop(mode);  // Call the base class stop
  }

  void Motor::setMaxCurrent(double current) {
    currentLimit = current;
  }

  void Motor::limitCurrent(double velocity) {
    // Current limiting logic
    if (velocity > -1 && velocity < 1) {
      setMaxTorque(0, vex::currentUnits::amp);
    } else {
      setMaxTorque(currentLimit, vex::currentUnits::amp);
    }
  }

}