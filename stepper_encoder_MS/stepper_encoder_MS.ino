#include <AS5600.h>
#include <Wire.h>
#include "A4988.h"
AMS_5600 ams5600;
float output;
#define SDA 27
#define SCL 13
#define MOTOR_STEPS 200
#define RPM 200
#define DIR 22
#define STEP 23
#define MS1 18
#define MS2 19
#define MS3 21
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);
float convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087;
  return retVal;
}
TaskHandle_t Task1;
void setup() {
  Wire.begin(SDA, SCL);
  Serial.begin(115200);
  if (ams5600.detectMagnet() == 0 ) {
    while (1) {
      if (ams5600.detectMagnet() == 1 ) {
        Serial.print("Current Magnitude: ");
        Serial.println(ams5600.getMagnitude());
        break;
      }
      else {
        Serial.println("Can not detect magnet");
      }
      delay(1000);
    }
  }
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);

  stepper.begin(RPM);
  stepper.enable();
  //  ams5600.setMaxAngle(360);
  //  ams5600.setStartPosition(0);
  //  stepper.setMicrostep(8);
  //  stepper.move(-8 * MOTOR_STEPS);
  //  int16_t Start= ams5600.getStartPosition();
  //  Serial.print("start : ");
  //  Serial.print(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
}
void Task1code( void * parameter ) {
  for (;;) {
    Serial.print("start : ");
    Serial.println(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
    //    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void loop() {
  //  delay(1000);
  //  Serial.print("before: ");
  //  Serial.println(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
  stepper.setMicrostep(2);   // Set microstep mode to 1:8
  //  //  while (ams5600.getScaledAngle() <= 360) {
  //stepper.move(2 * MOTOR_STEPS);    // forward revolution
  //  //  stepper.move(-8 * MOTOR_STEPS);   // reverse revolution
  //  stepper.rotate(360);
  //  //  stepper.rotate(-360);
  //  while (abs(convertRawAngleToDegrees(ams5600.getRawAngle())) <= 90) {
  //    stepper.setMicrostep(2);
  //    stepper.move(2 * MOTOR_STEPS);
  //    stepper.rotate(360);
  //    Serial.println(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
  //  }
  //  digitalWrite(DIR, 0);
  //  digitalWrite(STEP, 0);
  //  Serial.print("  after inside: ");
  //  Serial.println(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
  //  while (1);
  //  }
  //  Serial.println("outside while");
  //  stepper.move(0);
  //  stepper.rotate(0);
  if (Serial.available()) {
    int x = Serial.parseInt();
    stepper.rotate(x);
  }
}
