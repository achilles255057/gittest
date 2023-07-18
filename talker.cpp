#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "turn_turtle_node");
  ros::NodeHandle nh;

  // Create a publisher to control the turtle's movement
  ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

  // Set the rate at which the turtle turns
  double angular_speed = 90* M_PI / 180.0;  // Convert to radians per second

  // Set the desired angle for the turn
  double target_angle = 90.0 * M_PI / 180.0;  // Convert to radians

  // Calculate the time required to achieve the desired turn
  double turn_duration = target_angle / angular_speed;

  ros::Rate loop_rate(1.0 / turn_duration);  // Loop rate based on turn duration
  int count = 0;
  while (ros::ok()) {
    geometry_msgs::Twist speed;
    speed.linear.x = 1; 
    speed.linear.y = 0;
    speed.linear.z = 0;
    speed.angular.x = 0;
    speed.angular.y = 0;
    speed.angular.z = 0; 
    count++;

    while(count == 5)
    {
        ROS_INFO("slow down 1");
        speed.linear.x = 0.5; 
        count++;
    }
    while(count == 8)
    {
        ROS_INFO("slow down 2");
        speed.linear.x = 0.3; 
        count++;
    }
    while(count == 10)
    {
        count = 0;
        ROS_INFO("stop");
        speed.linear.x = 0; 

        // Create a twist message to send velocity commands
        geometry_msgs::Twist twist_msg;

        // Set the angular velocity to make the turtle turn
        twist_msg.angular.z = angular_speed;

        // Publish the twist message to start the turn
        twist_pub.publish(twist_msg);

        // Wait for the turn to complete
        ros::Duration(turn_duration).sleep();

        // Stop the turtle after the turn is complete
        twist_msg.angular.z = 0.0;
        twist_pub.publish(twist_msg);

        // Sleep to maintain the loop rate
        loop_rate.sleep();
    }

    // Publish the speed message to make the turtle move forward
    twist_pub.publish(speed);

    // Sleep to maintain the loop rate
    loop_rate.sleep();
  }

  return 0;
}
