// # Editor    : Steven Griset
// # Data      : 08.18.2013
// # Sonar System
// # URM37 V3.2 Ultrasonic Sensor from dfRobot
// # Product SKU:SEN0001
// # Version :  0.2
// # Motor Driver Shield
// # Ardumoto from Sparkfun
// # Product SKU:RTL-09896 
// # Description:
// # Robotic sound sensor control for autonomous system
// # Robot travels forward until it encounters a obsatcle within 10cm
// # Interrupt subroutine is triggered and robot stops, reverses and turns left
// # In this example will use the ISR function using a single pin Interrupt example


 
// # Sonar Connection:
// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 2 (Arduino)
// # 
// # Working Mode: Autonomous trigger mode
// # If it is your first time to use sonar module,please make sure the two jumpers to the right hand
// # side of the device are set to TTL mode. You'll also find a secondary jumper on 
// # the left hand side, you must break this connection or you may damage your device. 



#include <Servo.h>
Servo servo1;    //Create a servo object
Servo servo2;    //Create a second servo object

boolean motion = false;  //maneuver variable
int speed1= 3;   //left motor
int speed2 = 11;  //right motor
int direction1 = 12;  //left motor direction
int direction2 = 13;  //right motor direction

void stopMotor(){
  // turn both motors off
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
}


void forwardMotor(){
  //Both motors forward at full duty cycle
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, 255);
  analogWrite(speed2, 255);
}

void reverseMotor(){
  //Both motors forward at full duty cycle
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, 255);
  analogWrite(speed2, 255);
}

void leftfwdMotor(){
  //Both motors left turn forward at full duty cycle
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, 255);
  analogWrite(speed2, 255);
}



  
   

void setup() {
  
  bitSet(PCICR,PCIE2);  // enable pin change interrupt bank 2
  bitSet(PCMSK2, PCINT18);  //enable pin change interrupt on PCINT18/D2
  pinMode(speed1,OUTPUT);
  pinMode(speed2,OUTPUT);
  pinMode(direction1,OUTPUT);
  pinMode(direction2,OUTPUT);
  servo1.write(110);    // Put servo1 at home position
  servo2.write(100);    // Put servo2 at home position
}

void loop() {
  if(motion == true){
    maneuver();
    motion = false;
  }
  
    forwardMotor();
    

}

ISR(PCINT2_vect){      //interrupt handler when obstacle within 10cm or less 
  if(digitalRead(2) == LOW){
    motion = true;
  }
}




void maneuver(){    //manuever around obstacle with the following motion stop, reverse, trun left
  stopMotor();
  delay (1000);
  reverseMotor();
  delay(2000);
  leftfwdMotor();
  delay(2000); 
  return;
}
  
