// # Editor    : Steven Griset
// # Data      : 08.08.2016
// # Servo text for Rover One autonmous vehical  
// # Test the pan\tilt mast mechanism for Rover One using the standard Arduino Servo libaries 
// # Servo One is the x axis (bottom servo) and Servo Two is the y axis (top servo)
// # Usage is either X or x followed by a number between 15 and 170 then a Y or y followed by a number between 10 and 160
// # Example x160 y100, error handling is minmal and will often set the system to minmal values :-(
// *****************************************************************************************************************************


#include <Servo.h>

char buffer[10];
Servo servo1;    //Create a servo object
Servo servo2;    //Create a second servo object

void setup(){
  servo1.attach(5);    //Attaches the servo on pin 5 to the servo1 object
  servo2.attach(4);    //Attaches the servo on pin 4 to the servo2 object 
  Serial.begin(9600);
  Serial.flush();
  servo1.write(110);    // Put servo1 at home position
  servo2.write(100);    // Put servo2 at home position
  Serial.println("Starting ....");
}

void loop(){
  if(Serial.available() >0){
    //check if data has been entered
    int index=0;
    delay(100);    //Let the buffer fill up
    int numChar = Serial.available();    //Find the string length
    if(numChar >10){
      numChar =10;
    }
    while(numChar--){
      //Fill the buffer with the string
      buffer[index++] = Serial.read();
    }
    spiltString(buffer);    //Run splitString function
  }
}

void spiltString(char* data){
  Serial.print("Data entered:");
  Serial.println(data);
  char* parameter;
  parameter =strtok(data, " ,");  //String to token
  while(parameter != NULL){
    //if we haven't reached the end of the string...
    setServo(parameter);  //run the setServo function
    parameter =strtok(NULL, " ,");  //String to token
  }
  //Clear the text and serial buffers
  for(int x =0; x <9; x++){
    buffer[x] ='\0';
  }
 Serial.flush(); 
  
}

void setServo(char* data){
  if((data[0] =='X') || (data[0] =='x')){
    long firstVal = strtol(data+1, NULL, 10);    //String to long integer
    Serial.println(firstVal);
    firstVal = constrain(firstVal, 15, 170);  //Constrain values
    servo1.write(firstVal);
    Serial.print("Servo1 is set to:");
    Serial.println(firstVal);
    }
  if ((data[0] =='Y') || (data[0] =='y')){
    long secondVal = strtol(data+1,NULL, 10);  //String to long integer
    secondVal = constrain(secondVal, 10, 160);  //Constrain the values
    servo2.write(secondVal);
    Serial.print("Servo2 is set to:");
    Serial.println(secondVal);
    }
}

