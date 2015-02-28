/* This file has been created to try and fly the quadcopter using the joystic */

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <roscopter/RC.h>
#include <roscopter/APMCommand.h>

float joy_p_,joy_r_,joy_y_,joy_t_;

geometry_msgs::Twist twist_out;

void joy_callback(const sensor_msgs::Joy& joy_msg_in) //this also scales the joystick reading
{
	joy_p_ = joy_msg_in.axes[1];		//Pitch -- left stick up-down
	joy_r_ = joy_msg_in.axes[0];		//Roll -- left stick left-right
	joy_y_ = joy_msg_in.axes[3];		//Yaw -- right stick left-right
	joy_t_ = joy_msg_in.axes[4];
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "joycopter_controls");
	ros::NodeHandle node;
	ros::Rate loop_rate(50);

	ros::Subscriber joy_sub;
	joy_sub = node.subscribe("joy",1,joy_callback);

	ros::Publisher twist_pub;
	twist_pub = node.advertise<geometry_msgs::Twist>("new_u",1);

	float dead_zone = .15;
	
	while(ros::ok())
	{
	ros::spinOnce();

	twist_out.linear.z = joy_t_;
	twist_out.angular.y = joy_p_;
	twist_out.angular.x = joy_r_;
	twist_out.angular.z = joy_y_;

	twist_pub.publish(twist_out);
	loop_rate.sleep();
	}
	return 0;
}


