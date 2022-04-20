//#include <AccelStepper.h>
//#include <MultiStepper.h>
//
//
//#define MX_STP 25
//#define MX_DIR 33
//#define MY_STP 27
//#define MY_DIR 26
//#define LIMIT_X 15
//#define LIMIT_Y 4
//
//AccelStepper MX(1, MX_STP, MX_DIR);
//AccelStepper MY(1, MY_STP, MY_DIR);
//void motorInit();
//void homeXmoter(int x);
//void moveXmotor(int x);
//void homeYmoter(int x);
//void moveYmotor(int x);
//
//void motorInit()
//{
//  pinMode(LIMIT_X, INPUT_PULLUP);
//  pinMode(LIMIT_Y, INPUT_PULLUP);
//  MX.setMaxSpeed(1000);
//  MX.setAcceleration(1000);
//  MY.setMaxSpeed(1000);
//  MY.setAcceleration(1000);
//  MY.setSpeed(1000);
//  MY.setSpeed(1000);
//}
//
//void homeXmoter(int x = 1)
//{
//  MX.setMaxSpeed(400);
//  MX.setAcceleration(1000);
//  long initial_homing = 0;
//  while (digitalRead(LIMIT_X)) {  // Make the Stepper move CCW until the switch is activated
//    MX.moveTo(initial_homing);  // Set the position to move to
//    initial_homing = initial_homing + x; // Decrease by 1 for next move if needed
//    MX.run();  // Start moving the stepper
//    delay(5);
//  }
//  MX.setCurrentPosition(0);
//  MX.setMaxSpeed(1000);
//  MX.setAcceleration(1000);
//}
//
//
//void moveXmotor(int x = 1)
//{
//  long set = MX.currentPosition() + x;
//  set = constrain(set, 0, 230);
//  MX.moveTo(set);
//  MX.runSpeedToPosition();
//  //printf("Position x : %d\n",set);
//}
//
//
//
//
//
//
//void homeYmoter(int x = 1)
//{
//  MY.setMaxSpeed(400);
//  MY.setAcceleration(1000);
//  long initial_homing = 0;
//  while (digitalRead(LIMIT_Y)) {  // Make the Stepper move CCW until the switch is activated
//    MY.moveTo(initial_homing);  // Set the position to move to
//    initial_homing = initial_homing + x; // Decrease by 1 for next move if needed
//    MY.run();  // Start moving the stepper
//    delay(5);
//  }
//  MY.setCurrentPosition(0);
//  MY.setMaxSpeed(400);
//  MY.setAcceleration(1000);
// 
//
//}
//
//
//void moveYmotor(int x = 1)
//{
//  long set = MY.currentPosition() + x;
//  set = constrain(set, -700, 700);
//  MY.moveTo(set);
//  MY.runSpeedToPosition();
//  printf("Position y : %d\n", set);
//}
