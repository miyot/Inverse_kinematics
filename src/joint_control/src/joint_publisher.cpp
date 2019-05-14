#include "ros/ros.h"

#include "sensor_msgs/JointState.h"

#include "math.h"
#include <sstream>
#include <string>

int main(int argc, char **argv){
    ros::init(argc, argv, "visualize_joint_publisher");
    ros::NodeHandle n;

    //publisher
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);

    ros::Rate loop_rate(100);
    int count=0;
    while (ros::ok()){
        //publish joint states
        sensor_msgs::JointState js0;
        js0.header.stamp = ros::Time::now();
        js0.name.resize(12);
        js0.name[0]="jntFrontLeft1";
        js0.name[1]="jntFrontLeft3";
        js0.name[2]="jntFrontLeft4";
        js0.name[3]="jntFrontRight1";
        js0.name[4]="jntFrontRight3";
        js0.name[5]="jntFrontRight4";
        js0.name[6]="jntBackLeft1";
        js0.name[7]="jntBackLeft3";
        js0.name[8]="jntBackLeft4";
        js0.name[9]="jntBackRight1";
        js0.name[10]="jntBackRight3";
        js0.name[11]="jntBackRight4";
        js0.position.resize(12);
        js0.position[0]=-1.0*(float)count/40.0;
        js0.position[1]= 2.0*(float)count/40.0;
        js0.position[2]=-1.0*(float)count/40.0;
        js0.position[3]= 2.0*(float)count/40.0;
        js0.position[4]=-1.0*(float)count/40.0;
        js0.position[5]= 2.0*(float)count/40.0;
        js0.position[6]=-1.0*(float)count/40.0;
        js0.position[7]= 2.0*(float)count/40.0;
        js0.position[8]=-1.0*(float)count/40.0;
        js0.position[9]= 2.0*(float)count/40.0;
        js0.position[10]=-1.0*(float)count/40.0;
        js0.position[11]= 2.0*(float)count/40.0;
        // js0.velocity.resize(12);
        // js0.velocity[0]=-1.0*(float)count/40.0;
        // js0.velocity[1]= 2.0*(float)count/40.0;
        // js0.velocity[2]=-1.0*(float)count/40.0;
        // js0.velocity[3]= 2.0*(float)count/40.0;
        // js0.velocity[4]=-1.0*(float)count/40.0;
        // js0.velocity[5]= 2.0*(float)count/40.0;
        // js0.velocity[6]=-1.0*(float)count/40.0;
        // js0.velocity[7]= 2.0*(float)count/40.0;
        // js0.velocity[8]=-1.0*(float)count/40.0;
        // js0.velocity[9]= 2.0*(float)count/40.0; 
        // js0.velocity[10]=-1.0*(float)count/40.0;
        // js0.velocity[11]= 2.0*(float)count/40.0;
        joint_pub.publish(js0);
        count++;

        ros::spinOnce();
        loop_rate.sleep();
    } 
    return 0;
}