// # Editor    : Steven Griset
// # Data      : 09.04.2016
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
// # Robot also uses whisker triggers to dectect objects that make it pass the sonar system
// # Whisker Trigger system D8 left bumper and D6 is the right bumper 
// # Interrupt subroutine is triggered when switch is closed cart will take appropriate maneuver
// # Sonar Connection:
// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 2 (Arduino)
// # Whisker Triggers Connection:
//#        Left Bumper ->  Pin 8 (Arduino)        
// #       Right Bumper -> Pin 6 (Arduino)
// # Working Mode: Autonomous trigger mode
// # If it is your first time to use sonar module,please make sure the two jumpers to the right hand
// # side of the device are set to TTL mode. You'll also find a secondary jumper on 
// # the left hand side, you must break this connection or you may damage your device. 
// # This code has println code it for testing purposes 

#include <Servo.h>
Servo servo1;    //Create a servo object
Servo servo2;    //Create a second servo object
boolean motion = false;   //maneuver variable
const int bumpLeft = 8;  // Left bumper digital pin 8
const int bumpRight = 6; // Right bumper digital pin 6
const int Sonar =2;      //Sonar digital pin 2
boolean bLeft = false;   // boolean variable to hold left bumper switch state
boolean bRight = false;  // boolean varibale to hold right bumper switch state
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

void rightfwdMotor(){
  //Both motors right turn forward at full duty cycle
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, 255);
  analogWrite(speed2, 255);
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
  
   

void setup() {
  servo1.attach(5);    //Attaches the servo on pin 5 to the servo1 object
  servo2.attach(4);    //Attaches the servo on pin 4 to the servo2 object 
  bitSet(PCICR,PCIE2);  // enable pin change interrupt bank 2
  bitSet(PCMSK2, PCINT18);  //enable pin change interrupt on PCINT18/D2
  pinMode(bumpLeft, INPUT);
  pinMode(bumpRight, INPUT);
  bitSet(PCMSK2, PCINT22);  //enable pin change interrupt on PCINT22/D6
  bitSet(PCICR,PCIE0);  // enable pin change interrupt bank 0
  bitSet(PCMSK0, PCINT0);  //enable pin change interrupt on PCINT0/D8
  pinMode(speed1,OUTPUT);
  pinMode(speed2,OUTPUT);
  pinMode(direction1,OUTPUT);
  pinMode(direction2,OUTPUT);
  servo1.write(110);    // Put servo1 at home position
  servo2.write(100);    // Put servo2 at home position
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  if(motion == true){  // Sonar maneuver to avoid obstacle
  Serial.println("Maneuvering");
    maneuver();
    motion = false;
  }
  
   
  if(bRight == true){    //Right bumper hit routine
    Serial.println("Reversing");
    reverseMotor();
    delay(500);
    Serial.println("Left Forward");
    leftfwdMotor();
    delay (1500);
    bRight= false;
      }
  
  if(bLeft == true){    //Right bumper hit routine
    Serial.println("Reversing");
    reverseMotor();
    delay(500);
    Serial.println("Right Forward");
    rightfwdMotor();
    delay (1500);
    bLeft = false;
      }
  Serial.println("Forward");  
  forwardMotor();
}
// Pin change interrupt handlers for bank 2
ISR(PCINT2_vect){       
  if(digitalRead(Sonar) == LOW){    //interrupt handler when obstacle within 10cm or less
    motion = true;
  }
  if(digitalRead(bumpRight) == HIGH){  // Pin change Interrupt for right bumper
    bRight = true;
  }
}

// Pin change interrupt handlers for bank 0
ISR(PCINT0_vect){
  if(digitalRead(bumpLeft) == HIGH){  //Pin change Interrupt for left bumper 
    bLeft = true;
 } 
}


