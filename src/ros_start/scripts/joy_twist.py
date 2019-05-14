#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

class JoyTwist(object):
    def __init__(self):
        self.joy_sub = rospy.Subscriber('joy', Joy, self.joy_callback, queue_size=1)
        self.twist_pub = rospy.Publisher('/mobile_base/commands/velocity', Twist, queue_size=1)

    
    def joy_callback(self, joy_msg):
        twist = Twist()
        twist.linear.x = joy_msg.axes[1]
        twist.angular.z = joy_msg.axes[0]
        self.twist_pub.publish(twist)
    


if __name__ == "__main__":
    rospy.init_node('joy_twist')
    joy_twist = JoyTwist()
    rospy.spin()
