#include "ros/ros.h"
#include "geometry_msgs/Point.h"

void callback(const geometry_msgs::Point::ConstPtr& msg)
{
    ROS_INFO("UAV position: x=%f, y=%f, z=%f", msg->x, msg->y, msg->z);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "uav_subscriber");
    ros::NodeHandle nh;

    // 建立Subscriber，訂閱/UAV_pos這個topic，訊息型態為geometry_msgs/Point
    ros::Subscriber sub = nh.subscribe("/UAV_pos", 10, callback);

    ros::spin();

    return 0;
}
