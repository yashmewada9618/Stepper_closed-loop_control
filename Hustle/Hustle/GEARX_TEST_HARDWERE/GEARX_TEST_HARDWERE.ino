
#include <Ps3Controller.h>
#include "TFmini.h"
#include "motorclass.h"
#include "BluetoothSerial.h"
#include <TFMPlus.h>  // Include TFMini Plus Library v1.4.2


#define BUZZER_PIN 32
#define BUZZER_CHANNEL 2
BluetoothSerial SerialBT;

#define TF_RX 17
#define TF_TX 16

#define MX_STP 25
#define MX_DIR 33
#define MY_STP 27
#define MY_DIR 26
#define LIMIT_X 15
#define LIMIT_Y 4

motor moter(MX_STP, MX_DIR, LIMIT_X, MY_STP, MY_DIR, LIMIT_Y);
HardwareSerial TFSerial(1);

//TFmini tfmini;
TFMPlus tfmP;

int mathshit( int hight, int dis );
void tfMini( void *pvParameters );

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  //Ps3.attach(notify);
  //Ps3.attachOnConnect(onConnect);
  //Ps3.begin("96:49:f1:3b:be:34");
  TFSerial.begin(115200, SERIAL_8N1, TF_RX, TF_TX);
  //tfmini.attach(TFSerial);
  tfmP.begin( &TFSerial);
  moter.setLimitY(-10000, 10000);
  moter.setLimitX(-10000, 10000);
  moter.speedx = 1400;
  moter.speedy = 1400;
  pinMode(BUZZER_PIN, OUTPUT);
  //xTaskCreatePinnedToCore(tfMini, "tfMini" ,  10000,  NULL, 2,  NULL,  ARDUINO_RUNNING_CORE);
  //  xTaskCreatePinnedToCore(buzz, "buzz" ,  1000,  NULL, 2,  NULL,  ARDUINO_RUNNING_CORE);

}
int data = 0;
bool flag = 1;

bool flag2 = 0;
long f1, f2, f3, f4, f5;
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
int FluxThres = 50;
int16_t tfDistT = 0;    // Distance to object in centimeters
int16_t tfFluxT = 0;    // Strength or quality of return signal
int16_t tfTempT = 0;    // Internal temperature of Lidar sensor chip
bool printflag = 1;
bool buzzflag = 0;
long int first, second, diff;
void loop()
{
  if ( tfmP.getData( tfDist, tfFlux, tfTemp) && printflag) // Get data from the device.
  {
    // printf("%d -- %dt\n", tfDist, tfFlux);
    SerialBT.printf("X: %d- Y: %d- Dis: %d- Flx: %d \n", moter.posX(), moter.posY(), tfDist, tfFlux);
    delay(150);
  }
  while (SerialBT.available())
  {

    char data = SerialBT.read();
    if (data == 'B')
    {
      digitalWrite(BUZZER_PIN, 1);
      vTaskDelay(600);
      digitalWrite(BUZZER_PIN, 0);
      vTaskDelay(100);
      digitalWrite(BUZZER_PIN, 1);
      vTaskDelay(200);
      digitalWrite(BUZZER_PIN, 0);
    }
    if (data == 'b')
    {
      buzzflag = 1;
    }
    if (data == 'X')
    {
      SerialBT.printf("Time Taken :  %d", diff);
      moter.homeX(-1);
      diff = 0;
      printflag = 0;
    }

    if (data == 'Y')
    {

      moter.homeY(-1);
    }

    if (data == 'x')

    {
      int x = SerialBT.parseInt();
      Serial.println(data + (String)x);
      moter.setX(x);
      //      delay(200);
      //      if ( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
      //      {
      //        printf("%d -- %dt\n", tfDist, tfFlux);
      //
      //        while (1)
      //        {
      //          if (tfmath(tfDist, tfFlux) == 1)
      //            break;
      //        }
      //        printf("---%d---\n", millis());
      //      }
    }
    if (data == 'y')

    {
      int x = SerialBT.parseInt();
      Serial.println(data + (String)x);
      moter.setY(x);
    }
    if (data == 't')

    {
      FluxThres = SerialBT.parseInt();

    }
    if (data == 's')

    {
      printflag = !printflag;
    }
    if (data == 'd')
    {
      int x = SerialBT.parseInt();
      int y = SerialBT.parseInt();
      Serial.println(data + (String)x);
      moter.setXY(x, y);


      if (buzzflag)
      {
        buzzflag = 0;
        digitalWrite(BUZZER_PIN, 1);
        vTaskDelay(300);
        digitalWrite(BUZZER_PIN, 0);
        vTaskDelay(100);
        digitalWrite(BUZZER_PIN, 1);
        vTaskDelay(300);
        digitalWrite(BUZZER_PIN, 0);
        vTaskDelay(100);
        digitalWrite(BUZZER_PIN, 1);
        vTaskDelay(600);
        digitalWrite(BUZZER_PIN, 0);
      } else
        delay(300);
      if ( tfmP.getData( tfDistT, tfFluxT, tfTempT)) // Get data from the device.
      {
        printf("%d -- %dt\n", tfDist, tfFlux);

        if (diff == 0)
        {
          while (1)
          {
            if (tfmath(tfDistT, tfFluxT) == 1)
              break;
          }

        }
        first = millis();

        while (1)
        {
          if (tfmath(tfDistT, tfFluxT) == 1)
            break;
        }

        second = millis() - first;
        diff = diff + second;

        SerialBT.printf("---%d---\n", second);
      }
      digitalWrite(BUZZER_PIN, 1);
      vTaskDelay(200);
      digitalWrite(BUZZER_PIN, 0);
    }


  }
}

//
//
//
//void tfMini(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//  for (;;) // A Task shall never return or exit.
//  {
//    if (flag && tfmini.available())
//    {
//      SerialBT.printf("X Position: %d - Y Position: %d - DistanceTF : %d - Distance Laser : %d - Strength : %d \n" , moter.posX(), moter.posY(), (int)tfmini.getDistance(), mathshit(50, (int)tfmini.getDistance()), (int)tfmini.getStrength() );
//      Serial.printf("X Position: %d - Y Position: %d - DistanceTF : %d - Distance Laser : %d - Strength : %d \n" , moter.posX(), moter.posY(), (int)tfmini.getDistance(), mathshit(50, (int)tfmini.getDistance()), (int)tfmini.getStrength() );
//      yield();
//      delay(10);
//    }
//  }
//}
//
//
//
int mathshit( int hight, int dis)
{
  int b = hight;
  int c = dis;
  float a = sqrt(abs((c * c) - (b * b)));
  return ceil(a);
}




bool tfmath(int tfDistP, int tfFluxP )
{



  if ( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    delay(50);
    Serial.printf("%d   %d\n", tfFlux, tfFluxP);

    //SerialBT.printf("X: %d - D: %d S: %d\n" , moter.posX(), tfDist, tfFlux);



    //        if (abs(tfDist - tfDistP) < 10 && abs(tfFlux - tfFluxP) > FluxThres)
    //        {
    //          return 1;
    //        }
    //        else
    //        {
    //          return 0;
    //        }
    if ( abs(tfFlux - tfFluxP) > FluxThres)
    {
      Serial.printf("%d   %d\n", tfFlux, tfFluxP);

      return 1;
    }
    else
    {
      return 0;
    }

  }
  else
  {
    return 0;
  }

}
//
//
//
//
