// include Arduino stepper motor library
#include <Stepper.h>
#include <Servo.h>
// define number of steps per revolution
#define STEPS 32
// define stepper motor control pins
#define IN1  11
#define IN2  10
#define IN3   9
#define IN4   8
Servo myservo;
int lightSensor=A0,lightSensor2=A1;
int lightValue=0,lightValue2=0,pos=180,error=0;
bool lightDetected = false;
// initialize stepper library
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
// joystick pot output is connected to Arduino A0
void setup()

{
  myservo.attach(3);
  Serial.begin(9600);

}

 

void loop()

{
  lightValue= analogRead(lightSensor);
  lightValue2= analogRead(lightSensor2);
  error=abs(lightValue-lightValue2);
  Serial.println(lightValue);
  Serial.println(lightValue2);
  if (lightValue && lightValue2 >= 30)
  {
    lightDetected=true;
  }
  else
  {
    lightDetected=false;
    pos=180;
  }
  //LEFT & RIGHT
  if (lightValue > lightValue2 && error>10)
  {
   // set motor speed
   stepper.setSpeed(500);
   // move the motor (1 step)
   stepper.step(-5);
  }
  if (lightValue < lightValue2 && error >10)
  {
   // set motor speed
   stepper.setSpeed(500);
   // move the motor (1 step)
   stepper.step(5);
  }
  //UP & DOWN
  if (lightDetected == true)
  {
    if((lightValue && lightValue2 <= 40) && pos>=135)
    {
      pos--;
      delay(50);
    }
  }
  
  myservo.write(pos); 
  delay(15);
}
