#include <TFMPlus.h>
TFMPlus tfmP;
#define LED 2
void setup()
{
  Serial.begin( 115200);   // Intialize terminal serial port
  delay(20);               // Give port time to initalize
  pinMode(LED, OUTPUT);
  //    printf_begin();          // Initialize printf.
  Serial.println("TFMPlus Library");  // say 'hello'
  Serial2.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin( &Serial2);   // Initialize device library object and...
  Serial.println( "Soft reset: ");
  if ( tfmP.sendCommand( SYSTEM_RESET, 0))
  {
    Serial.println( "passed.\r\n");
  }
  else tfmP.printReply();
  delay(500);  // added to allow the System Rest enough time to complete
  // - - Display the firmware version - - - - - - - - -
  Serial.print( "Firmware version: ");
  if ( tfmP.sendCommand( OBTAIN_FIRMWARE_VERSION, 0))
  {
    digitalWrite(LED, 1);
    Serial.print(tfmP.version[ 0]); // print three single numbers
    Serial.print(".");
    Serial.print(tfmP.version[ 1]); // each separated by a dot
    Serial.print(".");
    Serial.println(tfmP.version[ 2]);
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  printf( "Data-Frame rate: ");
  if ( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    Serial.println("frame set to 5Hz and baud rate set");
    digitalWrite(LED, 0);
  }
  else tfmP.printReply();
  // - - - - - - - - - - - - - - - - - - - - - - - -
}

// Initialize variables
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
void loop()
{
  delay(50);   // Loop delay to match the 20Hz data frame rate

  if ( tfmP.getData(tfDist) && tfmP.getData(tfFlux) ) // Get data from the device.
  {
    if (tfDist >= 250 && tfDist <= 275) {
      digitalWrite(LED, 1);
      Serial.print( "in range: ");   // display distance,
      Serial.print(tfDist);
      Serial.print( " in range: ");   // display signal strength/quality,
      Serial.println(tfFlux);
    }
    else {
      Serial.print( "not range: ");   // display distance,
      Serial.print(tfDist);
      Serial.print( " not range: ");   // display signal strength/quality,
      Serial.println(tfFlux);
      digitalWrite(LED, 0);
    }
  }
  else                  // If the command fails...
  {
    tfmP.printFrame();  // display the error and HEX dataa
    digitalWrite(LED, 0);
  }
}
