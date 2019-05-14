#include "ros/ros.h"

#include "sensor_msgs/JointState.h"

#include "math.h"
#include <sstream>
#include <string>

int main(int argc, char **argv){
    ros::init(argc, argv, "visualize_joint_test_publisher");
    ros::NodeHandle n;

    //publisher
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);

    ros::Rate loop_rate(100);
    double count = -M_PI;
    double theta1 = 0,theta2 = 0,theta3 = 0;
    double x = 0,y = 0,z = 0;
    double a2 = 2,a3 = 2;
    double phi = 0,l = 0;
    while (ros::ok()){
        x = 1*cos(count); 
        z = sin(count) + 2; 
        y = 0;//1*sin(count);
        l = sqrt(z*z + x*x + y*y);
        if(y == 0)
            phi = atan2(x,z);
        else
            phi = atan2(sqrt(x*x + y*y)*x/fabs(x),z);
        theta3 = atan(y/x);
        theta2 = M_PI - acos((a2*a2 + a3*a3 - l*l)/(2*a2*a3));
        theta1 = phi - acos((a2*a2 + l*l - a3*a3)/(2*a2*l));
        //publish joint states
        sensor_msgs::JointState js0;
        js0.header.stamp = ros::Time::now();
        js0.name.resize(3);
        js0.name[0]="jntFrontLeft1";
        js0.name[1]="jntFrontLeft2";
        js0.name[2]="jntFrontLeft3";
        js0.position.resize(3);
        js0.position[0]= theta3;
        js0.position[1]= theta1;
        js0.position[2]= theta2;
        joint_pub.publish(js0);
        //if(count < M_PI){
            count+=0.03;
        //}
        ros::spinOnce();
        loop_rate.sleep();
    } 
    return 0;
}