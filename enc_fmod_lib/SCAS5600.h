#ifndef SCAS5600_h
#define SCAS5600_h

#include "Arduino.h"
#include <Wire.h>
class SCAS5600 {
  public:
    SCAS5600(short SDA, short SCL);
    float ReadRawAngle();
    float correctAngle();
    word checkQuadrant();
    word checkMagnetPresence();
  private:
    int magnetStatus = 0;
    int lowbyte;
    word highbyte;
    int rawAngle;
    float degAngle;
    int quadrantNumber, previousquadrantNumber;
    float numberofTurns = 0;
    float correctedAngle = 0;
    float totalAngle = 0;
    float startAngle = 0;
    float previoustotalAngle = 0;
};
#endif
