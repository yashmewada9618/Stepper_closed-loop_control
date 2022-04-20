int dist; /*----actual distance measurements of LiDAR---*/
int strength; /*----signal strength of LiDAR----------------*/
float temprature;
unsigned char check; /*----save check value------------------------*/
int i;
unsigned char uart[9]; /*----save data measured by LiDAR-------------*/
const int HEADER = 0x59; /*----frame header of data package------------*/
int rec_debug_state = 0x01;//receive state for frame
void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.println("\nBenewake TFmini-S UART LiDAR Program");
  Serial2.begin(115200);
}
void loop() {
  Get_Lidar_data();
}
void Get_Lidar_data() {
  if (Serial2.available()) //check if serial port has data input
  {
    if (rec_debug_state == 0x01)
    { //the first byte
      uart[0] = Serial2.read();
      if (uart[0] == 0x59)
      {
        check = uart[0];
        rec_debug_state = 0x02;
      }
    }
    else if (rec_debug_state == 0x02)
    { //the second byte
      uart[1] = Serial2.read();
      if (uart[1] == 0x59)
      {
        check += uart[1];
        rec_debug_state = 0x03;
      }
      else {
        rec_debug_state = 0x01;
      }
    }
    else if (rec_debug_state == 0x03)
    {
      uart[2] = Serial2.read();
      check += uart[2];
      rec_debug_state = 0x04;
    }
    else if (rec_debug_state == 0x04)
    {
      uart[3] = Serial2.read();
      check += uart[3];
      rec_debug_state = 0x05;
    }
    else if (rec_debug_state == 0x05)
    {
      uart[4] = Serial2.read();
      check += uart[4];
      rec_debug_state = 0x06;
    }
    else if (rec_debug_state == 0x06)
    {
      uart[5] = Serial2.read();
      check += uart[5];
      rec_debug_state = 0x07;
    }
    else if (rec_debug_state == 0x07)
    {
      uart[6] = Serial2.read();
      check += uart[6];
      rec_debug_state = 0x08;
    }
    else if (rec_debug_state == 0x08)
    {
      uart[7] = Serial2.read();
      check += uart[7];
      rec_debug_state = 0x09;
    }
    else if (rec_debug_state == 0x09)
    {
      uart[8] = Serial2.read();
      if (uart[8] == check)
      {

        dist = uart[2] + uart[3] * 256; //the distance
        strength = uart[4] + uart[5] * 256; //the strength
        temprature = uart[6] + uart[7] * 256; //calculate chip temprature
        temprature = temprature / 8 - 256;
        Serial.print("dist = ");
        Serial.print(dist); //output measure distance value of LiDAR
        Serial.print('\n');
        Serial.print("strength = ");
        Serial.print(strength); //output signal strength value
        Serial.print('\n');
        Serial.print("\t Chip Temprature = ");
        Serial.print(temprature);
        Serial.println(" celcius degree"); //output chip temperature of Lidar
        while (Serial2.available()) {
          Serial2.read(); // This part is added becuase some previous packets are
        }
        //        there in the buffer so to clear serial buffer and get fresh data.
        delay(100);
      }
      rec_debug_state = 0x01;
    }
  }
}
