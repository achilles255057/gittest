#include "ros/ros.h"
#include "geometry_msgs/Point.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "uav_publisher");
    ros::NodeHandle nh("~");

    // 讀取頻率參數，預設為1秒
    double frequency;
    nh.param<double>("frequency", frequency, 1.0);

    // 建立Publisher，發布到/UAV_pos這個topic上，訊息型態為geometry_msgs/Point
    ros::Publisher pub = nh.advertise<geometry_msgs::Point>("/UAV_pos", 10);

    ros::Rate rate(1.0 / frequency);  // 設定發布頻率

    // 設定無人機起始位置
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    while (ros::ok())
    {
        // 建立Point訊息
        geometry_msgs::Point point;
        point.x = x;
        point.y = y;
        point.z = z;

        // 發布訊息到/UAV_pos
        pub.publish(point);

        // 更新無人機位置
        x += 1.0;
        y -= 1.0;
        z += 1.0;

        rate.sleep();
    }

    return 0;
}
