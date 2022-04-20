#include <SCAS5600.h>
#include <AccelStepper.h>
int x = 0;
//#define DIR 22 //a4988
//#define STEP 23
#define DIR 26 //a4988
#define STEP 27
int c = 0;
//#define DIR 33 //drv
//#define STEP 25

//#define MS1 18
//#define MS2 19
//#define MS3 21

#define MS1 26 //drv
#define MS2 32
long init_steps = 0;
AccelStepper stepper(1, STEP, DIR);
SCAS5600 stepperenc(18, 19);
bool flag1 = false;
bool flag2 = false;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  //  pinMode(MS1, OUTPUT);
  //  digitalWrite(MS1, 1);
  stepper.setMaxSpeed(100000);
  //  stepper.setSpeed(stepper.maxSpeed());
  //  stepper.setAcceleration(100000);
  Serial.printf("setup with angle %.2f\n", stepperenc.ReadRawAngle());
}
void shortest_dist(word ang, int Speed = 2400) {
  while (1) {
    if ((stepperenc.ReadRawAngle() >= (ang - 0.9)) && (stepperenc.ReadRawAngle() <= (ang + 0.9))) {
      Serial.printf("motor moved at %.2f successfully\n", stepperenc.ReadRawAngle());
      delay(1);
      break;
    }
    else {
      if (fmod((ang - stepperenc.ReadRawAngle() + 360), 360) < 180) {
        Serial.printf("+++ %.2f\n", stepperenc.ReadRawAngle());
        //        c = abs((stepperenc.ReadRawAngle() - ang) / 1.8);
        stepper.moveTo(abs((stepperenc.ReadRawAngle() - ang) / 1.8));
        stepper.setSpeed(-Speed);
        stepper.run();
      }
      else {
        Serial.printf("--- %.2f\n", stepperenc.ReadRawAngle());
        //        c = abs((stepperenc.ReadRawAngle() - ang) / 1.8);
        stepper.moveTo(abs((stepperenc.ReadRawAngle() - ang) / 1.8));
        stepper.setSpeed(Speed);
        stepper.run();
      }
    }
    yield();
  }
}
void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'x') {
      int v = Serial.parseInt();
      int r = Serial.parseInt();
      shortest_dist(v, r);
      Serial.println("outside");
    }
  }
}
