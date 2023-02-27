#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "second_assignment/Service.h"

ros::Publisher pub; // publisher

// Initial variables
float velocity = 0;
float vel_lin = 1;
float vel_ang = 1;
float vel_max = 5;
float vel_min = 0;

double d_th = 1.5; // threshold distance

double scanner(double scan[], int size)
{
	double d_min = 100;
	for(int i=0; i < size; i++)
	{
		if(scan[i] < d_min)
		{
			d_min = scan[i];
		}
	}
	return d_min;
}

bool serviceFnc (second_assignment::Service::Request &req, second_assignment::Service::Response &res)
{
	if(req.command == 'w' && velocity < vel_max)
	{

		velocity += 1;
	}
	else if(req.command == 's' && velocity > vel_min)
	{

		velocity -= 1;
	}
	else if(req.command == 'r')
	{

		velocity = 0;
	}
        
	res.vel_final = velocity; // service's responce

	return true;
}


void robotCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	geometry_msgs::Twist vel;

	float scan[msg->ranges.size()];
	
	for(int k = 0; k < msg->ranges.size(); k++)
	{
		scan[k] = msg->ranges[k];
	}
	
	//3 subsections
	int section = (msg->ranges.size())/3;
	double left[section];
	double front[section];
	double right[section];
	
	for(int i = 0; i < section; i++)
	{
		right[i] = scan[i];
	}
	for(int i = 0; i < section; i++)
	{
		front[i] = scan[i + section];
	}
	for(int i = 0; i < section; i++)
	{
		left[i] = scan[i + 2*section];
	}

	// checking distance from wall
	if(scanner(front, section) < d_th)
	{	
	
		if(scanner(right,section) < scanner(left,section))
		{
			vel.angular.z = vel_ang;
			vel.linear.x = vel_lin;
		}
		else
		{
			vel.angular.z = -1 * vel_ang;
			vel.linear.x = vel_lin;
		}
	}
	else
	{
		//move forward
		vel.linear.x = velocity;
	}

	pub.publish(vel);

}

//main function
int main(int argc, char ** argv)
{
	ros::init(argc, argv, "robot_controller");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/base_scan", 100, robotCallback);
	ros::ServiceServer service = nh.advertiseService("/service", serviceFnc);

	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);

	ros::spin();
	return 0;

}
