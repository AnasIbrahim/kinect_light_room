/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/
#ifdef ARDUINO_MOTOR_PWM
  //PWM Pins only can pe used
  #define RIGHT_MOTOR_FORWARD  9
  #define RIGHT_MOTOR_BACKWARD 5
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_FORWARD   10
  #define LEFT_MOTOR_BACKWARD  6
  #define LEFT_MOTOR_ENABLE 13
#endif

#ifdef Sabertooth2x12
  #include <Servo.h>
  Servo leftMotor;
  Servo rightMotor;
  #define RIGHT_MOTOR  6
  #define LEFT_MOTOR   5
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
