#include <Servo.h>


// Ultrasonic var initialisation
const int trigPin = 12;
const int echoPin = 14;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;

float distanceCm;

// Servo var initialization
int pos = 0;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//Initialising ROS node
void setup() {

  // Ultrasonic setup 
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //Servo Setup
  myservo.attach(13);  // attaches the servo on GIO2 to the servo object
}

void loop() {

// Ultrasonic sensor read

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculate the distance
distanceCm = duration * SOUND_VELOCITY/2;



// Servo move
if (pos<180)
{
  pos = pos+1;

  if (pos>=180)
  {
    pos = pos-360;
  }
}
myservo.write(abs(pos));
delay(15);

Serial.println(distanceCm); 
Serial.println(abs(pos));
}
