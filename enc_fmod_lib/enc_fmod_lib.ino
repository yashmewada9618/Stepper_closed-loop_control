#include "SCAS5600.h"
#include <AccelStepper.h>
int x = 0;
#define DIR 22
#define STEP 23

#define MS1 18
#define MS2 19
#define MS3 21
long init_steps = 0;
AccelStepper stepper(1, STEP, DIR);
SCAS5600 myenc(27, 13);
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(MS2, OUTPUT);
  digitalWrite(MS2, 1);
  stepper.setMaxSpeed(100000);
  stepper.setSpeed(100000);
  stepper.setAcceleration(100000);
  Serial.printf("setup with angle %.2f\n", myenc.ReadRawAngle());
}
void shortest_dist(word ang = 0) {
  while (1) {
    if (myenc.ReadRawAngle() >= (ang - 0.9) && myenc.ReadRawAngle() <= (ang + 0.9)) {
      //      Serial.printf("motor moved at %.2f successfully\n", myenc.ReadRawAngle());
      delay(1);
      break;
    }
    else {
      //      myenc.ReadRawAngle();
      if (fmod((ang - myenc.ReadRawAngle() + 360), 360) < 180) {
        Serial.printf("motor homing in progress ++ \n");
        stepper.moveTo(init_steps);
        init_steps = init_steps + 1;
        stepper.run();
        //        ReadRawAngle();
      }
      else {
        Serial.printf("motor homing in progress -- \n");
        stepper.moveTo(init_steps);
        init_steps = init_steps - 1;
        stepper.run();
        //        ReadRawAngle();
      }
    }
    //  yield();
  }
}
void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'x') {
      int v = Serial.parseInt();
      //  int y = 1250;
      shortest_dist(v);
    }
  }
}
