#include <AccelStepper.h>
#define MS1 18
#define MS2 19
#define MS3 21
#define DIR 22
#define STEP 23
AccelStepper stepper(1, STEP, DIR);
void setup()
{
  Serial.begin(115200);
  pinMode(MS2, OUTPUT);
  digitalWrite(MS2, 1);
  stepper.setMaxSpeed(4000);
  stepper.setSpeed(500);
  stepper.setCurrentPosition(0);
  stepper.setAcceleration(10000);
}

void loop()
{
  digitalWrite(MS1, 1);
  if (Serial.available()) {
    char d = Serial.read();
    if (d == 'x')
    {
      int Final = Serial.parseInt();
      int y = Serial.parseInt();
      stepper.moveTo(Final);
      stepper.setSpeed(y);
      while (stepper.distanceToGo() != 0)
      {
        stepper.runSpeedToPosition();
      }
      Serial.printf("%.2f - %d\n", y, Final);
    }
  }
}
