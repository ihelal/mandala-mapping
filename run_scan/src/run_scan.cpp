#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <stdlib.h>
#include <ros/duration.h>
#include <ros/time.h>

int main(int argc, char **argv)
{
    //Initiate node and set hangle
    ros::init(argc, argv, "run_scan");
    ros::NodeHandle n;

    // Initialise published msgs
    ros::Publisher pubRequest = n.advertise<std_msgs::Bool>("m3d_test/aggregator/request",100);
    ros::Publisher pubVel = n.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel",100);

    //Get velocity and time period from parameter server
    float x_vel, x_vel_time;
    ros::param::get("x_vel", x_vel);
    ros::param::get("x_vel_time", x_vel_time);
    int pubRate = 10;
    int numVelMsgs = x_vel_time * pubRate;

    //Publish messages

    ros::Rate rate(pubRate);

    while(ros::ok())
    {
        //Publish scan request message
        std_msgs::Bool requestScan;
        requestScan.data = true;
        pubRequest.publish(requestScan);
        ros::Duration(15).sleep(); //wait for scan progress to reach 100%-takes ~12 seconds

        //Publish velocity commands
        geometry_msgs::Twist velmsg;
        velmsg.linear.x= x_vel;
        velmsg.angular.z=0;
        for(int i=0; i< numVelMsgs; i++)
        {
            pubVel.publish(velmsg);
            rate.sleep();
        }

        //Pause robot for 2 seconds to fully stop motion before scanning
        ros::Duration(2).sleep();
    }


}
