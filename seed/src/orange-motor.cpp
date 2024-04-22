// #include "orange-motor.h" # for some reason even after changing makefile this doesn't work
#include "../include/orange-motor.h"

namespace orange {
  void Motor::spin(vex::directionType dir, double velocity, vex::velocityUnits units) {
    setCurrentLimit(velocity);  // Implement current limiting
    vex::motor::spin(dir, velocity, units);  // Call the base class spin
  }

  void Motor::setMaxCurrent(double current) {
    currentLimit = current;
  }

  void Motor::setCurrentLimit(double velocity) {
    // Current limiting logic
    if (velocity == 0) {
      setMaxTorque(0, vex::currentUnits::amp);
    } else {
      setMaxTorque(currentLimit, vex::currentUnits::amp);
    }
  }

}