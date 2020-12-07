using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftIntake;
extern motor RightIntake;
extern motor LeftMovement;
extern motor RightMovement;
extern rotation Gyro;
extern distance Sonar;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );