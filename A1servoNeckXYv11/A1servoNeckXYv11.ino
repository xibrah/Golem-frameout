// input pos 2 servo control- mvj 1-4-2019
// mashed with zoomkat 11-22-10 servo (2) test
// ros2arduino implementation 9-25-2020
// refactor to Rosserial 10-16-2020
// split servo input to separate subscribers 03-11-22
// Current version 0.11 03-11-2022

#define USE_USBCON

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/String.h>


Servo myservo1;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos1 = 90;    // variable to store the servo position
int pos2 = 90;

ros::NodeHandle  nh;    //invoke NodeHandle as nh

String readStringX,readStringY, servo1, servo2;  //invoke strings

void servo_cbX( const std_msgs::String& cmd_msg){
  readStringX = atoi(cmd_msg.data);//set readString for neck X
}

void servo_cbY( const std_msgs::String& cmd_msg){
  readStringY = atoi(cmd_msg.data);//set readString for neck Y
}

ros::Subscriber<std_msgs::String> subX("neckX", servo_cbX); //listening address
ros::Subscriber<std_msgs::String> subY("neckY", servo_cbY);


void setup(){
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(subX);
  nh.subscribe(subY);

  myservo1.attach(2);  // attaches the servo on pin 2 to the servo object
  myservo2.attach(3);
}

void loop(){
  // put your main code here, to run repeatedly:
  if (readStringX.length() >0 ) {
      //Serial.println(readString); //see what was received
     
      // each subscriber expects a string like "123" containing the servo position     
      servo1 = readStringX.substring(0, 3); //get the first 3 characters into X
      //servo2 = readStringY.substring(0, 3); //get the first 3 characters into Y
     
      //Serial.println(servo1);  //print to serial monitor to see results
      //Serial.println(servo2);
     
     
      char carray1[6]; //magic needed to convert string to a number
      servo1.toCharArray(carray1, sizeof(carray1));
      pos1 = atoi(carray1);
     
      //char carray2[6];
      //servo2.toCharArray(carray2, sizeof(carray2));
      //pos2 = atoi(carray2);
     
      myservo1.write(pos1); //set servo position
      //myservo2.write(pos2);
      //readString="";
  }
  // separated for independent Y at servo2
  if (readStringY.length() >0) {
    // each subscriber expects a string like "123" containing the servo position     
      servo2 = readStringY.substring(0, 3); //get the first 3 characters into Y

      char carray2[6];
      servo2.toCharArray(carray2, sizeof(carray2));
      pos2 = atoi(carray2);
      
      myservo2.write(pos2);
  }
  
  
  nh.spinOnce();
  delay(1);
}
