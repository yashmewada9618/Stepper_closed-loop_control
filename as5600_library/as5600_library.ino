#include "SCAS5600.h"
#define SDA 27
#define SCL 13
SCAS5600 encoder;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  //  startAngle =
}

void loop() {
  // put your main code here, to run repeatedly:
  float output = encoder.ReadRawAngle();
  Serial.printf("angle : %.2f\n", output);
}
