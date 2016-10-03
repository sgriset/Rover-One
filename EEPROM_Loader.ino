// # Editor    : Steven Griset
// # Data      : 07.27.2013
 
// # URM37 V3.2 Ultrasonic Sensor from dfRobot
// # Product SKU:SEN0001
// # Version :  0.2
 
// # Description:
// # Robotic sound sensor control for autonomous system
// # This is a EEPROM loader program used to configure the sensor for use in Autonomous trigger mode 
 
 
// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 2 (Arduino)
// #       Pin 8 RXD (URM V3.2) -> Pin 0 (Arduino)
// #       Pin 9 TXD (URM V3.2) -> Pin 1 (Arduino) 
 
int cmmd1[]={
  0x44,0x00,0x0a,0x4e};//low byte stored in the sensor for the distance threshold. example (0x44 = command, 0x00 = low byte(data0), 0x0a = distance in cm (data1), checksum = command+data0+data1
int cmmd2[]={
  0x44,0x01,0x00,0x45};//high byte, write 0x01 into address 0x01 and 0x00,so the threshold is set to 10cm
int cmmd3[]={
  0x44,0x02,0xaa,0xf0};// Autonomous mode. write 0xaa into address 0x02
//int cmmd3[]={
//  0x44,0x02,0xbb,0x01};  // PWM mode. write 0xbb into address 0x02
int i;
 
void setup(){                                 
  Serial.begin(9600);                         // Sets the baud rate to 9600
  A_Mode_Setup();                             //Autonomus mode setup function
}
 
void loop()
{
}                      
 
void A_Mode_Setup(){ 
  //write the data into the URM37 EEPROM
  for (i=0;i<4;i++)
    Serial.write(cmmd3[i]);                             
  delay(200);                                           
 
  for (i=0;i<4;i++)
    Serial.write(cmmd1[i]);
  delay(200);
 
  for (i=0;i<4;i++)
    Serial.write(cmmd2[i]);
  delay(200);
 
}
