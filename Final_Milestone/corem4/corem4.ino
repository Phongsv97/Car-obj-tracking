#include "./corem4.h"+

#define SERVO_PIN 7

Servo servo;

char control_signal = 0;

void turnLeft();
void turnRight();
void forWard();
void stopMove();

int x = 90;
int pre_x = x;
int i =0;

void setup()
{
  servo.attach(SERVO_PIN);

  pinMode(leftWheel1, OUTPUT);
  pinMode(leftWheel2, OUTPUT);
  pinMode(rightWheel1, OUTPUT);
  pinMode(rightWheel2, OUTPUT);

  stopMove();

  /* Community with A9 */
  Serial.begin(115200);
}

void loop()
{
  control_signal = 0;
  if (Serial.available()) {
    control_signal = Serial.read() - 48;

    switch (control_signal) {
      case 1: { // turn right
        if (x > 70) {
          x -= 1;
          servo.write(x);
          break;
        } else {
          turnRight();
          break;
        }
    }

      case 2: {// turn left
        if (x < 120) {
          x += 1;
          servo.write(x);
          break;
        } else {
          turnLeft();
        }
      }

      case 4: { // xuong
          backWard();
          break;
      }

      case 5: {//len
        if (x <= 70) {//camera lech phai
          speedRight = 255;
          rightWheels_Backward();
          delay(5);
          
          speedRight = 55;
          rightWheels_Backward();
          delay(30);
          stopMove();

          for(i = 0; i < 10; i++) {
            control_signal = Serial.read() - 48;
            delay(1);
          }
          
          break;

        } else if (x >= 115) {//camera lech trai          
          speedLeft = 255;
          leftWheels_Backward();
          delay(5);
        
          speedLeft = 55;
          leftWheels_Backward();          
          delay(30);
          stopMove();

          for(i = 0; i < 10; i++) {
            control_signal = Serial.read() - 48;
            delay(1);
          }
         
          break;
        } else {
          forWard();
          break;
        }
      }

      case 0: {
        stopMove();
        break;
      }
    } // end switch
  } // end if

  control_signal = 0;
} // end loop

/********************** CONTROl FUNCTION ***************************/
void forWard()
{
  speedLeft = 255;
  speedRight = 255;
  rightWheels_Forward();
  leftWheels_Forward();
  delay(5);
  
  speedLeft = 35;
  speedRight = 35;
  rightWheels_Forward();
  leftWheels_Forward();
  delay(100);
  
  stopMove();
}
void backWard()
{
  speedLeft = 255;
  speedRight = 255;
  rightWheels_Backward();
  leftWheels_Backward();
  delay(5);

  speedLeft = 35;
  speedRight = 35;
  rightWheels_Backward();
  leftWheels_Backward();
  delay(100);

  stopMove();
}
void turnLeft()
{
  speedLeft = 255;
  speedRight = 255;
  rightWheels_Forward();
  leftWheels_Backward();
  delay(5);

  speedLeft = 55;
  speedRight = 55;
  rightWheels_Forward();
  leftWheels_Backward();
  delay(50);
  
  speedLeft = 95;
  speedRight = 95;
  rightWheels_Forward();
  leftWheels_Backward();
  delay(50);
  
  speedLeft = 155;
  speedRight = 255;
  rightWheels_Forward();
  leftWheels_Backward();
  delay(50);
  
  stopMove();
}
void turnRight()
{
  speedLeft = 255;
  speedRight = 255;
  rightWheels_Backward();
  leftWheels_Forward();
  delay(5);

  speedLeft = 55;
  speedRight = 95;
  rightWheels_Backward();
  leftWheels_Forward();
  delay(50);

  speedLeft = 95;
  speedRight = 95;
  rightWheels_Backward();
  leftWheels_Forward();
  delay(50);
  
  speedLeft = 255;
  speedRight = 155;
  rightWheels_Backward();
  leftWheels_Forward();
  delay(50);

  stopMove();
}

void stopMove()
{
  leftWheels_Stop();
  rightWheels_Stop();
  speedLeft = 125;
  speedRight = 90;
}
