/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftIntake           motor         3               
// RightIntake          motor         4               
// LeftMovement         motor         1               
// RightMovement        motor         2               
// Gyro                 rotation      9               
// Sonar                distance      10              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void turnDegrees(int degrees){
  Gyro.setPosition(0, rotationUnits::deg);
  double a = ((60 * 45)/degrees) * (degrees/360) * (94.0002221066) * (1/50.2654824574);  // exact rpm to move in degrees/45 seconds
  LeftMovement.setVelocity(a, velocityUnits::rpm);
  RightMovement.setVelocity(a, velocityUnits::rpm);
  RightMovement.spin(forward);
  wait((degrees/45), sec);
  RightMovement.setVelocity(0, velocityUnits::rpm);
}

void startMoving(){
  LeftMovement.setVelocity(100, velocityUnits::pct);
  RightMovement.setVelocity(100, velocityUnits::pct);
  LeftMovement.spin(forward);
  RightMovement.spin(forward);
}

void stopMoving(){
  LeftMovement.setVelocity(0, velocityUnits::pct);
  RightMovement.setVelocity(0, velocityUnits::pct);
}

void startIntake(){
  LeftIntake.setVelocity(100, velocityUnits::pct);
  RightIntake.setVelocity(100, velocityUnits::pct);
  LeftIntake.spin(forward);
  RightIntake.spin(forward);
}

void stopIntake(){
  LeftIntake.setVelocity(0, velocityUnits::pct);
  RightIntake.setVelocity(0, velocityUnits::pct);  
}

void autonomous(void){
  turnDegrees(90);
  while (Sonar.objectDistance(inches) > 2){
    startMoving();
  }
  stopMoving();

  startIntake();
  wait(2, sec);
  stopIntake();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    RightMovement.spin(forward);
    LeftMovement.spin(forward);
    if (abs(Controller1.Axis1.value()) > 20 || abs(Controller1.Axis4.value()) > 20) {
      double val = Controller1.Axis1.value() + Controller1.Axis4.value();
      RightMovement.setVelocity(-val + 27, velocityUnits::pct);
      LeftMovement.setVelocity(val + 27, velocityUnits::pct);
    }
    if (abs(Controller1.Axis2.value()) > 20 || abs(Controller1.Axis3.value()) > 20){
      double val = Controller1.Axis2.value() + Controller1.Axis3.value();
      RightMovement.setVelocity(val, velocityUnits::pct);
      LeftMovement.setVelocity(val, velocityUnits::pct);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
