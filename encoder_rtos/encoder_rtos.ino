#include <AccelStepper.h>
#include <AS5600.h>
#include <Wire.h>
AMS_5600 ams5600;
float output;
#define SDA 27
#define SCL 13

#define DIR 22
#define STEP 23
AccelStepper stepper(1, STEP, DIR); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
TaskHandle_t Task1;
int Initial;
void setup()
{
  Wire.begin(SDA, SCL);
  //  if (ams5600.detectMagnet() == 0 ) {
  //    while (1) {
  //      if (ams5600.detectMagnet() == 1 ) {
  //        Serial.print("Current Magnitude: ");
  //        Serial.println(ams5600.getMagnitude());
  //        break;
  //      }
  //      else {
  //        Serial.println("Can not detect magnet");
  //      }
  //      delay(1000);
  //    }
  //  }
  //  pinMode(18, OUTPUT);
  //  pinMode(19, OUTPUT);
  //  pinMode(21, OUTPUT);
  //  digitalWrite(18, 1);
  //  digitalWrite(19, 0);
  //  digitalWrite(20, 0);
  Serial.begin(115200);
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);
  stepper.setMaxSpeed(4000);
  stepper.setSpeed(500);
  stepper.setCurrentPosition(0);
  stepper.setAcceleration(10000);
  Initial = convertRawAngleToDegrees(ams5600.getRawAngle());
  Serial.printf("Initial angle: %d\n", Initial);
  ams5600.setOutPut(1);
}
float convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087;
  return retVal;
}

void Task1code( void * parameter ) {
  //  Serial.print("Task1 is running on core ");
  //  Serial.println(xPortGetCoreID());
  for (;;) {
    //    Serial.print("start : ");
    //    Serial.printf("Initial angle: %d\n", Initial);
    Serial.printf("angle: %f\n", convertRawAngleToDegrees(ams5600.getRawAngle()));
    delay(50);
  }
}

void loop()
{
  if (Serial.available()) {
    char d = Serial.read();
    if (d == 'x')
    {
      int Final = Serial.parseInt();
      int y = Serial.parseInt();
      int moveto = (Final - Initial);
      if (moveto < 0) {
        moveto = moveto + 360;
      }
      else {}
      //    stepper.setSpeed(y);
      //    stepper.runSpeed();
      stepper.moveTo(moveto / 1.8);
      stepper.setSpeed(y);
      while (stepper.distanceToGo() != 0)
      {
        // stepper.runSpeed();
        stepper.runSpeedToPosition();
        //        Serial.printf("%d\n", stepper.distanceToGo());
      }
      //      Initial = Final;
      Serial.printf("%.2f - %d\n", convertRawAngleToDegrees(ams5600.getRawAngle()), Final);
    }
  }

}
