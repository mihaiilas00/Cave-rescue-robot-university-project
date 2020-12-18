//#include <Adafruit_MotorShield.h>

void operate_grabber(bool command)
{
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
  
  myMotor3->setSpeed(grabber_closer_speed);         //need to test to get best value
  
  if (command==0)
  {
    myMotor3->run(FORWARD);  //need to test to see if this is correct
  }
  if (command==1)
  {
    myMotor3->run(BACKWARD);  //need to test to see if this is correct
  }
  delay(grabber_closer_time);
  myMotor3->run(RELEASE); //stop motors
  
}

void ramp(bool command)
{
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);
  
  myMotor4->setSpeed(ramp_speed);         //need to test to get best value
  
  if (command==0)
  {
    myMotor4->run(FORWARD);  //need to test to see if this is correct
  }
  if (command==0)
  {
    myMotor4->run(BACKWARD);  //need to test to see if this is correct
  }
  delay(ramp_time);
  myMotor3->run(RELEASE); //stop motors
}
