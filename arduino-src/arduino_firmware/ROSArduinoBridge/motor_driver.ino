/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#if defined POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined ARDUINO_MOTOR_PWM
  void initMotorController() {
    //do noting
    //enable the H-bridge enable-signal for the 2 motor
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
    //Serial.println("ARDUINO_MOTOR_PWM initialized");
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
  
    if (spd < 0)
    {
      spd = -spd;  // Make speed a positive quantity
      reverse = 1;  // Preserve the direction
    }
    if (spd > 255) // Max PWM dutycycle
      spd = 255;

    //spd = spd  * 51 / 80;
    
    if (i == LEFT) { 
      //Serial.print("LEFT  ");
      //Serial.println(spd);
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_FORWARD, spd); analogWrite(RIGHT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_BACKWARD, spd); analogWrite(RIGHT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      //Serial.print("Right ");
      //Serial.println(spd);
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_FORWARD, spd); analogWrite(LEFT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_BACKWARD, spd); analogWrite(LEFT_MOTOR_FORWARD, 0); }
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }  
#elif defined Sabertooth2x12
   void initMotorController() {
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
  }
  
  void setMotorSpeed(int i, int spd) {
    //spd = 150;
    //next chunck of line are made to convert the lenght of speed from (-255 : 255) to (1000 to 1500) as first number is backward and second if forward
    //calculating right speed
      long rightSpeed;
      rightSpeed = spd;
      rightSpeed += 255;
      rightSpeed = int(rightSpeed * 100 / 51);
      rightSpeed += 1000;
    //calculating left speed
      long leftSpd = - spd;
      leftSpd += 255;
      leftSpd = int(leftSpd * 100 / 51);
      leftSpd += 1000;
    
    if (i == LEFT) { 
      //check range first
//        if (leftSpd > 2000)   { Serial.print("left  forward speed error\n");   }
//        if (leftSpd < 1000)   { Serial.print("left  backward  speed error\n"); }  
//      Serial.print("LEFT ");
//      Serial.print(leftSpd);
//      Serial.print(" ");
//      Serial.print(spd);
//      Serial.print("\n");
//      Serial.print("\t"); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! delete
      leftMotor.writeMicroseconds(leftSpd);
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      //check range first
//        if (rightSpeed > 2000)  { Serial.print("right backward speed error\n");  }
//        if (rightSpeed < 1000)  { Serial.print("right forward speed error\n");   }
//      Serial.print("Right ");
//      Serial.print(rightSpeed);
//      Serial.print(" ");
//      Serial.print(spd);
//      Serial.print("\n");
      rightMotor.writeMicroseconds(rightSpeed);
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }

#else
  #error A motor driver must be selected!
#endif

#endif
