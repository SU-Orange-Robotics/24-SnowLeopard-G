#pragma once

#include "vex.h"

namespace orange {

class Motor : public vex::motor {
public:
  void spin(vex::directionType dir, double velocity, vex::velocityUnits units);

  void setMaxCurrent(double current);

private:
  double currentLimit = 2.5;  // Maximum current in amps

	void setCurrentLimit(double velocity);
};

}