/************************************************/
#include <Servo.h>
/************************************************/
Servo gasServo;//create servo object
Servo brakeServo;

void setup()
{
  Serial.begin(9600);  // start serial port at 9600 bps:
  gasServo.attach(9);//attachs the servo on pin 9 to servo object
  brakeServo.attach(10);//attachs the servo on pin 9 to servo object

  gasServo.write(0);//back to 0 degrees 
  brakeServo.write(0);//back to 0 degrees 
  delay(1000);//wait for a second
}
/*************************************************/
void loop()
{ 
  gasServo.write(0);
  delay(1000);
  brakeServo.write(0);
  delay(1000); 
  gasServo.write(60);
  delay(1000);
  brakeServo.write(60);

  delay(1000);
}
/**************************************************/
