/*Obstacle-Avoiding-Car-Code*/
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>
#include <Servo.h>

#define LEFT_LED A0
#define RIGHT_LED A1
#define trig_Pin A3
#define echo_Pin A2
#define MAX_SPEED 150 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20


AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;
int Time = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(70);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
  delay(2000);
}

void loop()
{
    myservo.write(70);

    digitalWrite(LEFT_LED, LOW);
    digitalWrite(RIGHT_LED, LOW);
  distance = obstacle();
  Serial.println(distance);
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 15)
  { digitalWrite(LEFT_LED, HIGH);
    digitalWrite(RIGHT_LED, HIGH);
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      turnRight();
      moveStop();
    } else
    {
      turnLeft();
      moveStop();
    }
  }
  else
  {
    moveForward();
  }

}
int obstacle()
{
  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_Pin, LOW);
  Time = pulseIn(echo_Pin, HIGH);
  distance = (Time / 29.1) / 2;
  if (distance < 0)
    distance = 0;
  if (distance > 200)
    distance = 200;
  return distance;
}
int lookRight()
{
  myservo.write(0);
  delay(500);
  distance = obstacle();
  delay(200);
  myservo.write(70);
  return distance;
}

int lookLeft()
{
  myservo.write(170);
  delay(500);
  distance = obstacle();
  delay(200);
  myservo.write(70);
  return distance;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {

  if (!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(2000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(2000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
