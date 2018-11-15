//LED's blinking at front
#define LED 2
//**********************************************************************


//HCSR04 PINS 
#define trig 12
#define echo 13

//HCSR04-left PINS 
#define trigl 10
#define echol 11

//defining global variables
float duration, distance;
//**********************************************************************

//DC Motors connected via L298N 
//Motor side A
int enA = 9;
int in1 = 8;
int in2 = 7;

//Motor side B
int enB = 3;
int in3 = 5;
int in4 = 4;
//**********************************************************************

void setup() {
  // set both head led's to output.
  pinMode(LED, OUTPUT);
  
  //set all motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //using the hcsro4
  pinMode(trig, OUTPUT);
  pinMode(trigl, OUTPUT);
}
//**********************************************************************

//function to turn left
void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, 0);
  analogWrite(enB, 200);  
  
  //led blink code
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
}
//**********************************************************************

//function to turn right
void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 200);
  analogWrite(enB, 0);  
  //led blink code
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
}
//**********************************************************************

//function to move forward
void speed()
{
  //running the motors at a speed range 0 to 255.
  //max speed depends on total supplied voltage.

  //turning on motors in forward direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Accelarate from 0 to max speed
  analogWrite(enA, 350);
  analogWrite(enB, 350);
  //led blink code
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
}
//**********************************************************************

//funtion to stop the bot
void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  //Accelarate from 0 to max speed
  analogWrite(enA, 0);
  analogWrite(enB, 0); 
  //led blink code
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
}
//**********************************************************************

//funtion to move the bot backwards
void back(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4, LOW);

  //Accelarate from 0 to max speed
  analogWrite(enA, 150);
  analogWrite(enB, 150); 
  //led blink code
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  delay(50);
}
//**********************************************************************

//function for pulse at left -- if detected -- turns left
void pulsel(){
  //write a pulse to the HC - SR04 left sensor
  digitalWrite(trigl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);

  //measuring the response of echo
  duration = pulseIn(echol, HIGH);

  //determinig distance from duration
  //using 343 meters per sec as speed of sound
  distance = (duration/2)*0.0343;

  //sends results to motor to take direction
  if (distance >= 40){
    speed();
  }
  else{
    stop();
    right();
  }
delay(500);
}
//**********************************************************************
//**********************************************************************

//function for pulse -- turns left -- makes left hcsr04 active
void pulse(){
  //write a pulse to the HC - SR04 left sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //measuring the response of echo
  duration = pulseIn(echo, HIGH);

  //determinig distance from duration
  //using 343 meters per sec as speed of sound
  distance = (duration/2)*0.0343;

  //sends results to motor to take direction
  if (distance >= 40){
    speed();
  }
  else{
    stop();
    pulsel();
  }
delay(500);
}
//**********************************************************************

//// function for bluetooth module
//void bluetooth(){
//  while(Serial.available())
//  {
//    char data;
//    data = Serial.read();
//    if(data =='F') // speed
//    {
//      speed();
//    }
//    else if(data =='L') //left
//    {
//      left();
//    }
//    else if(data =='R') //right
//    {
//      right();
//    }
//    else if(data =='B') //back
//    {
//      back();
//    }
//    else
//    {
//      pulse();
//    }
//  }
//}
////**********************************************************************

void loop() {
  // put your main code here, to run repeatedly:
  pulse();
}



