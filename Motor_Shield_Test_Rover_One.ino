// # Editor    : Steven Griset
// # Data      : 07.05.2016 
// # DC Motor Test system for Rover One Project
// # Part List for Project
// # Arduino Pro 386 - 5V/16MHz
// # Ardumoto from Sparkfun Motor Control Shield
// # Description:
// # Sketch to test motor shield hardware and software control functions
// # Software control functions include 
// # Stop, Forward, Reverse, Left Turn and Right Turn
// # Missing is the set speed function, this sketch does not take dynamic input  
// # **************************************************************************** 


// digital pin variables for direction and speed
int speed1= 3;   //left motor speed control
int speed2 = 11;  //right motor speed control
int direction1 = 12;  //left motor direction
int direction2 = 13;  //right motor direction


// Motor Contorl funtions

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


void setup() {
  
  // configure digital pins as Out pins
  pinMode(speed1,OUTPUT);
  pinMode(speed2,OUTPUT);
  pinMode(direction1,OUTPUT);
  pinMode(direction2,OUTPUT);
  
  // setup serial monitoring of sketch
  Serial.begin(9600);
  Serial.flush();

}

void loop() {
  Serial.println("Spin DC Motors forward for 8 seconds");
  forwardMotor();
  delay(8000);
  
  Serial.println("Spin DC Motors reverse for 8 seconds");
  reverseMotor();
  delay(8000);
  
  Serial.println("Turn DC Motors left for 8 seconds");
  leftfwdMotor();
  delay(8000);
  
  Serial.println("Turn DC Motors right for 8 seconds");
  rightfwdMotor();
  delay(8000); 
  
  Serial.println("Stop DC Motors for 8 seconds");
  stopMotor();
  delay(8000);
  
  
}
