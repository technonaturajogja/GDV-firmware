#include <Arduino.h> // Comment this line if you are using Arduino IDE, only uses this if you are using PlatformIO

#define motorKiri 10, 11
#define motorKanan 6, 9

int pwm1,pwm2;

void moveMotor(unsigned int motorPinA, unsigned int motorPinB, int speed){
  if(speed >= 0){
  	analogWrite(motorPinA, speed);
    analogWrite(motorPinB, 0);
  }

else{
    analogWrite(motorPinA, 0);
    analogWrite(motorPinB, speed*-1);
  }
}
void setup() {
  // put your setup code here, to run once:
//   Serial.begin(115200); // Start Serial Communication
}

void loop() {
  // put your main code here, to run repeatedly:

  // Looping if there is serial data received
  while(Serial.available()>0){
    uint8_t data[6]; // declaring the data buffer // reading data from serial

    // if the first and the last received data are synchrone with the real data
    if(data[0] == 's' && data[5] =='d'){
        // in this particular application, we use serial to send velocity values of each motor in arduino
        // since uint8_t only receive data from 0-255, which doesn't contain minus, hence we need an element
        // in the array data to specify if it's minus or plus
        if(data[1] == 0) {
          pwm1 = data[2]*-1;
        }
        else{
          pwm1 = data[2];
        }
        if(data[3] == 0) {
          pwm2 = data[4]*-1;
        }
        else{
          pwm2 = data[4];
        }
        

        moveMotor(motorKiri, pwm1);
        moveMotor(motorKanan, pwm2);
    }
  }
}
