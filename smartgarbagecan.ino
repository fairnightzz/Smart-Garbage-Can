#include <Time.h>
#include <TimeLib.h>

#include <Servo.h>
//Setting up the servo
int pos;
int pos1;
Servo garbageServo;
Servo garbageServo1;

//Ultrasonic Sensor
/*
 * There are 4 pins: Ground, VCC, Trigger, and Echo
 * Trigger sends a signal to echo and echo sends an echo and sees how long it takes to get back the echo.
 * Set Trig pin to 3 and echo pin to 4
 * We also need a duration and distance variable
 * 
 * 
 */

 //for sensing hand
 int trigPin = 6;
 int echoPin = 7;
 long durationSensor;//how long the wave takes to reach back
 int distanceSensor;//calculated distance in cm
//for sensing if garbage is full
//Other ultrasonic to sense if garbage is full
 int trigPin1 = 3;
 int echoPin1 = 4;
 long durationSensor1;
 int distanceSensor1;
 boolean moving=false;//if the hand is sensed, needs to keep up for a few seconds. 
//Time Function
time_t t = now(); //in seconds

//Piezo
const int buzzerPin = 8;
/*
 *  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
 */

int weekButton = 5;
int weekButtonState;//either 0 or 1

int openButton = 9;
int openButtonState;

//Photoresistor
const int pResistor = A0;
int light;

//Temperature Sensor
int tempPin = A1;

//Motor Pin for fan
int motorPin = 2;

 
void setup() {
  // put your setup code here, to run once:
  //Setting up ultrasonic input output
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(buzzerPin, OUTPUT);
  garbageServo.attach(11);
  garbageServo1.attach(12);

  //Motor Fan
  pinMode(motorPin,OUTPUT);

  //Photoresistor
  pinMode(pResistor,INPUT);
  
  //Setup printing and debugging in the monitor
  Serial.begin(9600);
  setTime(0); // Set the system time to the variable
}


void loop() {//Main Loop
  //Reads the light input
  light=analogRead(pResistor);
  //The temperature in the back
  int reading = analogRead(tempPin);
  float voltage = reading * 5.0;
  voltage/=1024.0;//calculated voltage
  float temperatureC = (voltage - 0.5) * 100 ;//In celsuis 
  if (temperatureC>24){//if the temperature is above room temp, use fan
    //Serial.println("Motor");
    analogWrite(motorPin,255);
  }
  //Ultrasonic Sensor
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationSensor = pulseIn(echoPin, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  // Calculating the distance
  distanceSensor= durationSensor*0.034/2;//Gives distance in cm
  //Other ultrasonic for garbage sensing
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  durationSensor1 = pulseIn(echoPin1, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  // Calculating the distance
  distanceSensor1= durationSensor1*0.034/2;//Gives distance in cm
  //If garbage is detected within 10 cm and the distance sensor isn't 0 cm (because the sensor isn't perfect), along with light being dark so that it doesn't start beeping when you throw garbage in, start sound.
  if (distanceSensor1<10 and distanceSensor1!=0 and light<350){
    Serial.println("Garbage fulll");

    //Super cool song
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
  }
  
  if (distanceSensor<30 and distanceSensor!=0){//If the ultrasonic sensor sees the hand
    Serial.print("Distance: ");
    Serial.println(distanceSensor);
    moving=true;//set moving to true
  }
  else{//turn it off
    moving=false;
  }
  //This button is to remind the user to take out the garbage after one week.
  weekButtonState = digitalRead(weekButton);
  if (weekButtonState==LOW){//Reset time
    setTime(0);
    Serial.println("Set Time");
  }
  else if (t>604800){//amount of seconds in a week
    Serial.println("Garbage Time");

    //Super cool song
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
    tone(buzzerPin, 262, 100);
    delay(100);
    tone(buzzerPin, 494, 100);
    delay(100);
  }
  openButtonState = digitalRead(openButton);
  if (openButtonState==LOW){//Reset time
    moving=true;
    Serial.println("Open can");
  }
  
  if (moving==true and pos != 180 and pos1!=0){//This is to move the garbage can
    pos1 = 180;
    //Or we could use this:
    for (pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      garbageServo.write(pos);              // tell servo to go to position in variable 'pos'
      garbageServo1.write(pos1);
      pos1-=1;
      Serial.println("Moving up");
      Serial.println(pos1);
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(5000);//waits 5 seconds for user to put garbage in
  }
  
  else if (moving==false and pos!=0 and pos1!=180){
    pos1=0;
    //then moving back:
    for (pos = 180; pos > 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      garbageServo.write(pos);
      garbageServo1.write(pos1);
      pos1+=1;
      Serial.println("Moving Down");// tell servo to go to position in variable 'pos'
      Serial.println(pos1);
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
