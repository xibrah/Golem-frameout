#include <ros/ros.h>
#include <std_msgs/Float32.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "test-panXY");
	ros::NodeHandle n;
	ros::Publisher test-publisherXY = n.advertise<std_msgs::Float32>("topicXY", );
	
	std_msgs::Float32 input_float;
	input_float.data = 0.0;
	
	while (ros::ok())
	{
		//loop burns cpu time - no sleep timer
		input_float.data = input_float.data + 0.001; //increment on loop
		test-publisherXY.publish(input_float); //publish as float32
	}
}
