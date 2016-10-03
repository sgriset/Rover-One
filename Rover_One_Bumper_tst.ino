 // # Editor    : Steven Griset
// # Data      : 08.08.2016
// # Whisker Trigger Test for autonmous robot cart 
// # Test Whisker Trigger system for D8 left bumper and D6 is the right bumper 
// # Interrupt subroutine is triggered when switch is closed cart will take appropriate maneuver
// # This setup can also be used for a follow a wall cart system

const int bumpLeft = 8;  // Left bumper digital pin 8
const int bumpRight = 6;  // Right bumper digital pin 6
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
// the setup routine runs once when you press reset:
void setup() {
  pinMode(bumpLeft, INPUT);
  pinMode(bumpRight, INPUT);
  bitSet(PCICR,PCIE2);  // enable pin change interrupt bank 2
  bitSet(PCMSK2, PCINT22);  //enable pin change interrupt on PCINT22/D6
  bitSet(PCICR,PCIE0);  // enable pin change interrupt bank 0
  bitSet(PCMSK0, PCINT0);  //enable pin change interrupt on PCINT0/D8
  Serial.begin(9600);
  Serial.flush();
} 

void loop() {
  
  
  if(bRight == true){    //Right bumper hit routine
    reverseMotor();
   // Serial.println("Im reversing");
    delay(500);
    leftfwdMotor();
   // Serial.println("Im making a left turn");
    delay (1500);
    bRight= false;
      }
  
  if(bLeft == true){    //Right bumper hit routine
    reverseMotor();
   // Serial.println("Im reversing");
    delay(500);
    rightfwdMotor();
   // Serial.println("Im making a right turn");
    delay (1500);
    bLeft = false;
      }  
      forwardMotor();
     // Serial.println("I'm going forward");
}
// Pin change Interrupt for right bumper
ISR(PCINT2_vect){
  if(digitalRead(bumpRight) == HIGH){
    bRight = true;
  }
 }
//Pin change Interrupt for left bumper 
ISR(PCINT0_vect){
  if(digitalRead(bumpLeft) == HIGH){
    bLeft = true;
 } 
}
