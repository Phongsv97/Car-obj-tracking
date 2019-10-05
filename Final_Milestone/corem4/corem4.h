#ifndef _CORE_M4_H_
#define _CORE_M4_H_

#include <Servo.h>

#define leftWheel1 3  // pwm pin
#define leftWheel2 4

#define rightWheel1 5   // pwm pin
#define rightWheel2 6

unsigned int speedLeft = 125;
unsigned int speedRight = 90;

/* control Right Wheel */
#define rightWheels_Forward() \
  do                                        \
  {                                         \
    analogWrite(rightWheel1, speedRight);    \
    digitalWrite(rightWheel2, LOW);   \
  } while (0)

#define rightWheels_Backward()                      \
  do                                        \
  {                                         \
    analogWrite(rightWheel1, 255 - speedRight);   \
    digitalWrite(rightWheel2, HIGH);    \
  } while (0)

#define rightWheels_Stop()                     \
  do                                       \
  {                                        \
    analogWrite(rightWheel1, 255);    \
    digitalWrite(rightWheel2, HIGH);   \
  } while (0)

    /* control Left Wheel */
#define leftWheels_Forward()                     \
  do                                      \
  {                                       \
    analogWrite(leftWheel1, speedLeft);   \
    digitalWrite(leftWheel2, LOW);    \
  } while (0)

#define leftWheels_Backward()                    \
  do                                      \
  {                                       \
    analogWrite(leftWheel1, 255 - speedLeft);    \
    digitalWrite(leftWheel2, HIGH);   \
  } while (0)

#define leftWheels_Stop()                    \
  do                                      \
  {                                       \
    analogWrite(leftWheel1, 255);    \
    digitalWrite(leftWheel2, HIGH);   \
  } while (0)

#endif /* _CORE_M4_H_ */
