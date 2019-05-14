
#include "ros/ros.h"  
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"

enum class joint_name{
  frontLeft,
  frontRight,
  backLeft,
  backRight,
  joint_sum
};

enum class joint_number{
  one,
  three,
  four,
  number_sum
};

using namespace std;
// std_msgs::Float64 tmp_joint[static_cast<int>(joint_name::joint_sum)][static_cast<int>(joint_number::number_sum)];
// int number = 0;
// void monitorJointState(const sensor_msgs::JointState::ConstPtr& jointstate)
// {
//   for(int i = 0; i < static_cast<int>(joint_name::joint_sum); ++i){
//     for(int j = 0; j < static_cast<int>(joint_number::number_sum); ++j){
//       tmp_joint[i][j].data = jointstate->position[number];
//       number++;
//     }
//   }
// }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joint_move");  // ノードの初期化
  ros::NodeHandle nh; // ノードハンドラ  
  ros::Publisher pub_joint[static_cast<int>(joint_name::joint_sum)][static_cast<int>(joint_number::number_sum)]; // パブリッシャの作成
  //ros::Subscriber sub_joints, sub_sensor;  // サブスクライバの作成

  std_msgs::Float64 target_joint[static_cast<int>(joint_name::joint_sum)][static_cast<int>(joint_number::number_sum)];

  pub_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::one)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontLeft1_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::three)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontLeft3_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::four)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontLeft4_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::one)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontRight1_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::three)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontRight3_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::four)] = nh.advertise<std_msgs::Float64>("/four_legs/jntFrontRight4_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::one)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackLeft1_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::three)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackLeft3_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::four)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackLeft4_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::one)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackRight1_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::three)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackRight3_position_controller/command", 100);
  pub_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::four)] = nh.advertise<std_msgs::Float64>("/four_legs/jntBackRight4_position_controller/command", 100);

  //sub_joints = nh.subscribe("/four_legs/joint_states", 100, monitorJointState);

  target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::one)].data = 0;
  target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::three)].data = 0;
  target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::four)].data = 0;
  target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::one)].data = 0;
  target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::three)].data = 0;
  target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::four)].data = 0;
  target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::one)].data = 0;
  target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::three)].data = 0;
  target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::four)].data = 0;
  target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::one)].data = 0;
  target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::three)].data = 0;
  target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::four)].data = 0;

  double count = 0;
  double theta1 = 0,theta2 = 0,theta3 = 0;
  double x = 0,y = 0,z = 0;
  double a2 = 0.2,a3 = 0.2;
  double phi = 0,l = 0;
  while (ros::ok()) { 
     ros::Rate loop_rate(100);
    for(int i = 0; i < static_cast<int>(joint_name::joint_sum); ++i){
      for(int j = 0; j < static_cast<int>(joint_number::number_sum); ++j){
        pub_joint[i][j].publish(target_joint[i][j]);// 角度を送信 
      }
    }  
    x = 0.07*cos(-count); 
    z = 0.02*sin(-count) + 0.35; 
    y = 0;//0.07*sin(-count);
    l = sqrt(z*z + x*x + y*y);
    if(y == 0)
        phi = atan2(x,z);
    else
        phi = atan2(sqrt(x*x + y*y)*x/fabs(x),z);
    theta3 = atan(y/x);
    theta2 = M_PI - acos((a2*a2 + a3*a3 - l*l)/(2*a2*a3));
    theta1 = phi - acos((a2*a2 + l*l - a3*a3)/(2*a2*l));


    target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::one)].data = theta3;
    target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::three)].data = theta1;
    target_joint[static_cast<int>(joint_name::frontLeft)][static_cast<int>(joint_number::four)].data = theta2;
    target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::one)].data = theta3;
    target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::three)].data = theta1;
    target_joint[static_cast<int>(joint_name::backRight)][static_cast<int>(joint_number::four)].data = theta2;



    x = 0.07*cos(-count+M_PI); 
    z = 0.02*sin(-count+M_PI) + 0.35; 
    y = 0;//*sin(-count+M_PI);
    l = sqrt(z*z + x*x + y*y);
    if(y == 0)
        phi = atan2(x,z);
    else
        phi = atan2(sqrt(x*x + y*y)*x/fabs(x),z);
    theta3 = atan(y/x);
    theta2 = M_PI - acos((a2*a2 + a3*a3 - l*l)/(2*a2*a3));
    theta1 = phi - acos((a2*a2 + l*l - a3*a3)/(2*a2*l));

    target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::one)].data = theta3;
    target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::three)].data = theta1;
    target_joint[static_cast<int>(joint_name::frontRight)][static_cast<int>(joint_number::four)].data = theta2;
    target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::one)].data = theta3;
    target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::three)].data = theta1;
    target_joint[static_cast<int>(joint_name::backLeft)][static_cast<int>(joint_number::four)].data = theta2;
    count+= 0.08;
    ros::spinOnce(); 
    loop_rate.sleep();
    
  }
  
  return 0;
}