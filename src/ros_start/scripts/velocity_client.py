#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from ros_start.srv import SetVelocity
import sys

if __name__ == "__main__":
    rospy.init_node('velocity_client')
    set_velocity = rospy.ServiceProxy('set_velocity', SetVelocity)
    linear_vel = float(sys.argv[1])
    angular_vel = float(sys.argv[2])
    response = set_velocity(linear_vel, angular_vel)
    if response.success:
        rospy.loginfo('set [{},{}] success'.format(linear_vel, angular_vel))
    else:
        rospy.logerr('set [{},{}] failed'.format(linear_vel, angular_vel))
        
