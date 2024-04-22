#include "vex.h"
#include "drive.h"
#include "robot-config.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// 8 motor 4 WHEEL mechanum drive
// A front, B back
motor LeftMotorA(PORT17, gearSetting::ratio18_1, false);
motor LeftMotorB(PORT18, gearSetting::ratio18_1, true);
motor LeftMotorC(PORT15, gearSetting::ratio18_1, false);
motor RightMotorA(PORT12, gearSetting::ratio18_1, true);
motor RightMotorB(PORT13, gearSetting::ratio18_1, false);
motor RightMotorC(PORT14, gearSetting::ratio18_1, true);

motor intake(PORT20, gearSetting::ratio18_1, false);

motor climberA(PORT11, gearSetting::ratio18_1, true);
motor climberB(PORT19, gearSetting::ratio18_1, false);

motor climberArm(PORT1, gearSetting::ratio18_1, false);

motor wingL(PORT9, gearSetting::ratio18_1, false);
motor wingR(PORT8, gearSetting::ratio18_1, true);

motor ballKicker(PORT2, gearSetting::ratio18_1, true);

inertial imu(PORT15);
gps gps1(PORT4, 0, 0, distanceUnits::mm, 180); // port, x, y, distance units, angle offset, turn direction?


// ----- not used -----
motor catapultA(PORT11, gearSetting::ratio18_1, false); //left
motor catapultB(PORT19, gearSetting::ratio18_1, false); //right
rotation catapultRot(PORT5, false);

rotation odomLeft(PORT10, true);
rotation odomRight(PORT2, false);
rotation odomCenter(PORT3, true);

optical colorSensor(PORT14);
// ----- end not used ----

brain Brain;
controller Controller1(controllerType::primary);

vex::digital_out soleA(Brain.ThreeWirePort.H);

// declare object-oriented stuff here (that should be globally accessible)
Drive drive;
Wings wings;