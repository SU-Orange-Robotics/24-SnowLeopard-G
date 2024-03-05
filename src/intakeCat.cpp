#include "vex.h"
#include "robot-config.h"
#include "intakeCat.h"

using namespace vex;

bool autoArming = false;

void intakeSpin(bool reversed) {
    intake.spin(directionType::fwd, intakePow * (reversed ? -1 : 1), percentUnits::pct);
}

void intakeStop() {
    intake.stop();
}

void catapultLower(int pow) {
    catapultA.spin(directionType::fwd, pow, percentUnits::pct);
    catapultB.spin(directionType::fwd, pow, percentUnits::pct);
}

void catapultRaise() {
    catapultA.spin(directionType::fwd, catPow * -1, percentUnits::pct);
    catapultB.spin(directionType::fwd, catPow * -1, percentUnits::pct);
}

void catapultStop() {
    catapultA.stop();
    catapultB.stop();
}

void catapultArm() {
    autoArming = true;
    catapultLower();
    waitUntil(catInPosArmed() || !autoArming);
    catapultStop();
    autoArming = false;
}

void catapultArmToPosition(double pos) {
    
}

void catapultLaunch() {
    catapultLower();
    waitUntil(catapultRot.velocity(velocityUnits::dps) > 2);
    catapultStop();
}

bool catInPosArmed() {
    double setPos = 62; //197.57, 197.75

    double currPos = catapultRot.angle(rotationUnits::deg);
    return (currPos <= setPos);
}

/*bool catInPosShoot() {
    double posA1 = 248, posA2 = 255;

    double currPos = catapultRot.angle(rotationUnits::deg);
    //modf(360, &currPos);

    return (currPos > posA1 && currPos < posA2);
}*/

double velo;
double lastVelo;
double catAccel = 0;

/** Updates the accelleration value for the catapult
 * @param time
 * the amount of time elapsed since last update in seconds
 */
void updateCatAccel(double time) {
    velo = catapultRot.velocity(velocityUnits::dps);
    catAccel = (velo - lastVelo) / time; // time in seconds
    lastVelo = velo;
}

double getCatAccel() {
    return catAccel;
}

void stopAutoArming() {
    autoArming = false;
}