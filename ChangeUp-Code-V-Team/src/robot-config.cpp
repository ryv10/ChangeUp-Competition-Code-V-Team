#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftIntake = motor(PORT3, ratio18_1, false);
motor RightIntake = motor(PORT4, ratio18_1, false);
motor LeftMovement = motor(PORT1, ratio18_1, false);
motor RightMovement = motor(PORT2, ratio18_1, false);
rotation Gyro = rotation(PORT9, false);
distance Sonar = distance(PORT10);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}