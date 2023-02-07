// The reason why servo is acting so shit is because of pulseIn(echoPin, HIGH). Ultrasonic sensor waits for sound to come back
// and if it dosen't then it keeps on waiting and hence extra delay is added. 
// *** TO DO ***
// If pulseIn  takes more than 10 microsecond then tell it to SHUT THE FUCK UP

#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Range.h>


// Ultrasonic var initialisation
const int trigPin = 12;
const int echoPin = 14;

#define SOUND_VELOCITY 0.034


long duration = 0;

float distanceCm = 0;

// Servo var initialization
int pos = 0;

//Initialising ROS node
ros::NodeHandle  nh;
std_msgs::Float32 ultra_to_ros;
sensor_msgs::Range range_msgs;

ros::Publisher ultrasonic_pub("ultrasonic_pub",&range_msgs); 
char frameid[] ="/sonar_ranger";

// twelve servo objects can be created on most boards
Servo myservo;  // create servo object to control a servo
//Initialising ROS node
void setup()
{
    // Ultrasonic setup 
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    //Servo Setup
    myservo.attach(13);  // attaches the servo on GIO2 to the servo object

    // ROS setup
    nh.initNode();
    nh.advertise(ultrasonic_pub);

    range_msgs.field_of_view = (10.0 / 180.0)*3.14;
    range_msgs.min_range = 0.0;
    range_msgs.max_range = 100.0;
    range_msgs.radiation_type = sensor_msgs::Range::ULTRASOUND;
    range_msgs.header.frame_id = frameid;
    
}

void loop()
{
    /* Servo motor turning clockwise */
    for(pos = 0; pos<180; pos++)
    {
        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);

        // Calculate the distance
        distanceCm = duration * SOUND_VELOCITY/2;

        range_msgs.range = distanceCm;
        myservo.write(pos);
        delay(15);

        ultrasonic_pub.publish(&range_msgs);
        nh.spinOnce();
    }

    /* Servo motor turingi anticlockwise */
    for(pos = 180; pos >=0; pos--)
    {
        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);

        // Calculate the distance
        distanceCm = duration * SOUND_VELOCITY/2;

        range_msgs.range = distanceCm;

        // Calculate the distance
        distanceCm = duration * SOUND_VELOCITY/2;
        range_msgs.range = distanceCm;

        ultrasonic_pub.publish(&range_msgs);
        nh.spinOnce();

        myservo.write(pos);
        delay(15);
    }  
}





// // Ultrasonic sensor read

// // Clears the trigPin
// digitalWrite(trigPin, LOW);
// delayMicroseconds(2);
// // Sets the trigPin on HIGH state for 10 micro seconds
// digitalWrite(trigPin, HIGH);
// delayMicroseconds(10);
// digitalWrite(trigPin, LOW);

// // Reads the echoPin, returns the sound wave travel time in microseconds
// duration = pulseIn(echoPin, HIGH);

