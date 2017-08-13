#include <Servo.h> 
 
Servo x_servo;
Servo y_servo;
 
int pos = 0;
 
void setup() 
{ 
  //revise all limits as axis got inverted
  x_servo.attach(9);
  //x_limits:
  //  hard limits: 50 - 145
  //  soft limits: 60 - 135
  y_servo.attach(10);
  //y_limits:10 - 170
  //there is actually no limits
} 
 
void loop() 
{ 
  //move to a specific position----------------------------
  x_servo.write(70);
  y_servo.write(70);
  //-------------------------------------------------------
  //sweep--------------------------------------------------
//  for(pos = 0; pos <= 180; pos += 1)
//  {
//    myservo.write(pos);
//    delay(15);
//  } 
//  for(pos = 180; pos>=0; pos-=1)
//  {   
//    myservo.write(pos);
//    delay(15);
//  }
  //-------------------------------------------------------
} 

