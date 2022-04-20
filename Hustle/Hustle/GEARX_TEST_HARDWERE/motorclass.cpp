#include"motorclass.h"



motor::motor(int _xstp, int _xdir, int _xlimit, int _ystp, int _ydir, int _ylimit)
{
  AccelStepper _MX(1, _xstp, _xdir);
  AccelStepper _MY(1, _ystp, _ydir);
  MX = _MX;
  MY = _MY;
  // delete _MX;
  //  delete _MY;
  xlimit = _xlimit;
  ylimit = _ylimit;
  pinMode(xlimit, INPUT_PULLUP);
  pinMode(ylimit, INPUT_PULLUP);
  MX.setMaxSpeed(4000);
  MX.setAcceleration(10000);
  MY.setMaxSpeed(4000);
  MY.setAcceleration(10000);
  MY.setMaxSpeed(4000);
  MX.setMaxSpeed(4000);
}

void  motor::homeX(int x)
{
  MX.setSpeed(40);
  MX.setAcceleration(2000);
  int initial_homing = 0;
  while (digitalRead(xlimit))
  {
    MX.moveTo(initial_homing);
    initial_homing = initial_homing + x;
    MX.run();
    delay(5);
  }
  setPosX(0);
  MX.setSpeed(speedx);

}


void  motor::homeY(int x )
{
  MY.setSpeed(40);
  MY.setAcceleration(2000);
  int initial_homing = 0;
  while (digitalRead(ylimit))
  {
    MY.moveTo(initial_homing);
    initial_homing = initial_homing + x;
    MY.run();
    delay(5);
  }
  setPosY(0);
  MY.setSpeed(speedy);
}
void  motor::homeXY(int x , int y )
{
  homeX(x);
  homeY(y);
}


int  motor::moveY(int x )
{
  int set = MY.currentPosition() + x;
  set = constrain(set, ymin, ymax);
  MY.moveTo(set);
  MY.setSpeed(speedy);
  MY.runSpeedToPosition();
  return set;
}
int  motor::moveX(int x)
{
  int set = MX.currentPosition() + x;
  set = constrain(set, xmin, xmax);
  MX.moveTo(set);
  MX.setSpeed(speedx);
  MX.runSpeedToPosition();
  return set;
}

void  motor::moveXY(int x = 1, int y = 1)
{
  moveX(x);
  moveY(y);
}

void  motor::setY(int set)
{

   MY.moveTo(set);
  MY.setSpeed(speedy);
  while (MY.distanceToGo()!=0)
  {
   // MX.runSpeed();
     MY.runSpeedToPosition();
  }

}
void  motor::setX(int set)
{

  //  set = constrain(set, xmin, xmax);
  MX.moveTo(set);
  MX.setSpeed(speedx);
  while (MX.distanceToGo()!=0)
  {
   // MX.runSpeed();
     MX.runSpeedToPosition();
  }
 

}

void  motor::setXY(int  x, int y)
{
  setX(x);
  setY(y);
}

int  motor::posX()
{
  return MX.currentPosition();
}


int  motor::posY()
{

  return MY.currentPosition();

}

void  motor::setPosX(int x)
{
  MX.setCurrentPosition(x);
}


void  motor::setPosY(int y)
{

  MY.setCurrentPosition(y);

}


void  motor::setSpeedX(int _s)
{
  speedx = _s;
  MX.setSpeed(speedx);
}

void  motor::setSpeedY(int _s)
{
  speedy = _s;
  MY.setSpeed(speedy);
}


void motor::setLimitX(int min, int max)
{
  xmin = min;
  xmax = max;
}

void motor::setLimitY(int min, int max)
{
  ymin = min;
  ymax = max;
}
