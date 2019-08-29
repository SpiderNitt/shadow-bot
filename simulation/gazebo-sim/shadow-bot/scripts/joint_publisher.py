#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64
import numpy as np

class JointPub(object):
    def __init__(self):
        self.t = 0.0
        self.publishers_array = []
        self.left_arm_joint = rospy.Publisher('/left_arm_joint_pc/command', Float64, queue_size=1)
        self.right_arm_joint = rospy.Publisher('/right_arm_joint_pc/command', Float64, queue_size=1)

        self.publishers_array.append(self.left_arm_joint)
        self.publishers_array.append(self.right_arm_joint)

    def move_joints(self, joints_array):
   
        i=0
        for publisher in self.publishers_array:
          joint_value = Float64()
          joint_value.data=joints_array[i]
          rospy.loginfo(str(joint_value)+" on "+str((publisher.name).split('/')[2]) + " @rate: " + str(rate_value))    
          self.left_arm_joint.publish(joint_value)
          self.right_arm_joint.publish(joint_value)
          publisher.publish(joint_value)
          i = i+1
        rospy.loginfo("---------------") 


    def start_loop(self, rate_value = 2.0, dt=1.0/2):
        rospy.loginfo("Starting Control")
        omega = 2
        theta = 0.0*np.pi
        sign = 1
        rate = rospy.Rate(rate_value)
        while not rospy.is_shutdown():
          self.t += dt
          theta = 0.25*np.pi #+ 0.1*np.pi*np.sin(omega*self.t)
          pos = [theta, theta]
          self.move_joints(pos)
          rate.sleep()


if __name__=="__main__":

  try:
    rospy.init_node('joint_publisher_node')
    joint_publisher = JointPub()

    #** tweak the publication rate **#
    rate_value = 10
    joint_publisher.start_loop(rate_value=rate_value, dt=1.0/rate_value)

  except rospy.ROSInterruptException:
    pass