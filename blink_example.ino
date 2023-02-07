// ** Servo without Delay *

#include <Servo.h>

// --------CONSTANTS (won't change)---------------

const int servoPin = 13; // the pin number for the servo signal
const int trigPin = 12;
const int echoPin = 14;

const int servoMinDegrees = 20; // the limits to servo movement
const int servoMaxDegrees = 150;

Servo myservo;  // create servo object to control a servo 

int servoPosition = 90;     // the current angle of the servo - starting at 90.
int servoInterval = 10; // millisecs between servo moves
int servoDegrees = 2;       // amount servo moves at each step 
                            //    will be changed to negative value for movement in the other direction

unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
unsigned long currentMicros = 0;

unsigned long previousServoMillis = 0; // the time when the servo was last moved

// ** Ultrasonic stuff**

unsigned long previousUltraMicros = 0; // the time for ultrasonic stuff
int ultraIntervalClean = 2; // interval to clean Ultrasonic

//define sound velocity in cm/uS
float SOUND_VELOCITY = 0.034;

long duration = 0 ;

float distanceCm = 0;


//========================================

void setup() {

    Serial.begin(9600);
    Serial.println("Starting SeveralThingsAtTheSameTimeRev1.ino");  // so we know what sketch is running

    myservo.write(servoPosition); // sets the initial position
    myservo.attach(servoPin);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void loop() {

        // Notice that none of the action happens in loop() apart from reading millis()
        //   it just calls the functions that have the action code

    currentMillis = millis();   // capture the latest value of millis()
                                //   this is equivalent to noting the time from a clock
                                //   use the same time for all LED flashes to keep them synchronized
    currentMicros = micros();

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    servoSweep();

}

void servoSweep() {

      // this is similar to the servo sweep example except that it uses millis() rather than delay()

      // nothing happens unless the interval has expired
      // the value of currentMillis was set in loop()
  
  if (currentMillis - previousServoMillis >= servoInterval) {
        // its time for another move
    previousServoMillis += servoInterval;
    
    servoPosition = servoPosition + servoDegrees; // servoDegrees might be negative

    if ((servoPosition >= servoMaxDegrees) || (servoPosition <= servoMinDegrees))  {
          // if the servo is at either extreme change the sign of the degrees to make it move the other way
      servoDegrees = - servoDegrees; // reverse direction
          // and update the position to ensure it is within range
      servoPosition = servoPosition + servoDegrees; 
    }
    
        // make the servo move to the next position
    myservo.write(servoPosition);
        // and record the time when the move happened

  }
  
}
