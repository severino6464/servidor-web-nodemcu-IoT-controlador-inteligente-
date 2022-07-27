#include <GY6050.h>           //library for GYRO 
#include <Wire.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int X = 0;
int Y = 0;
GY6050 gyro(0x68);              //to save GYRO data


void setup() {

  Wire.begin();            //initializing GYRO
  gyro.initialisation();
  delay(100);
  myservo.attach(2);
   Serial.begin(9600);
}

void loop() {
  X = map(gyro.refresh('A', 'X'), -90, 90, 30, 0);                //mapping the gyro data according to angle limitation of servo motor 
  Y = map(gyro.refresh('A', 'Y'), -15, 15, 0, 30);
  myservo.write(Y);  
  Serial.print("valor de y ===================== ");
  Serial.println(Y);
 delay(15);

}
