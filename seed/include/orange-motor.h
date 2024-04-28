#pragma once

#include "vex.h"

namespace orange {

class Motor : public vex::motor {
public:
  Motor(int32_t port, vex::gearSetting gear = vex::gearSetting::ratio18_1, bool isReversed = false, double currentLimit = 2.5)
      : vex::motor(port, gear, isReversed) {
    this->currentLimit = currentLimit;
    this->setMaxTorque(currentLimit, vex::currentUnits::amp);
  }

  // try to use these two functions instead of the other base class functions
  void spin(vex::directionType dir, double velocity, vex::percentUnits units);
  void stop(vex::brakeType mode = vex::brakeType::brake);
  
  void setMaxCurrent(double current);

private:
  double currentLimit = 2.5;  // Maximum current in amps

	void limitCurrent(double velocity);
};

}