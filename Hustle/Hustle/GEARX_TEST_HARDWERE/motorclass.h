#ifndef motorclass_h
#define motorclass_h
#include <AccelStepper.h>


class motor
{
  public:
    motor(int _xstp, int _xdir, int _xlimit, int _ystp, int _ydir, int _ylimit);
    int xlimit, ylimit;
    int speedx = 400, speedy = 400;
    int xmin = -10000, xmax = 10000;
    int ymin = -10000, ymax = 10000;
    AccelStepper MX;
    AccelStepper MY;
    void homeX(int x );
    void homeY(int y );
    void homeXY(int x , int y );
    int moveX(int x);
    int moveY(int Y);
    void moveXY(int x, int y);
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    void setLimitX(int min, int max);
    void setLimitY(int min, int max);
    int posX();
    int posY();
    void setPosY(int y);
    void setPosX(int x);
    void setSpeedX(int x);
    void setSpeedY(int y);


};
#endif
