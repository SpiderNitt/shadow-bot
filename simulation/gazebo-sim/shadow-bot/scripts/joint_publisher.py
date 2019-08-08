#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64

class JointPub(object):
    def __init__(self):

        self.publishers_array = []
        self.left_arm_joint = rospy.Publisher('/shadow/left_arm_joint/command', Float64, queue_size=1)
        self.right_arm_joint = rospy.Publisher('/arboc/right_arm_joint/command', Float64, queue_size=1)

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
        rospy.loginfo("*************************************************************************************") 


    def start_loop(self, rate_value = 2.0):
        rospy.loginfo("Starting Control")
        pos1 = [-1.0,1.0]
        pos2 = [1.0,-1.0]
        position = "pos1"
        rate = rospy.Rate(rate_value)
        while not rospy.is_shutdown():
          if position == "pos1":
            self.move_joints(pos1)
            position = "pos2"
          else:
            self.move_joints(pos2)
            position = "pos1"
          rate.sleep()


if __name__=="__main__":

  try:
    rospy.init_node('joint_publisher_node')
    joint_publisher = JointPub()

    #** tweak the publication rate **#
    rate_value = 0.5
    joint_publisher.start_loop(rate_value)

  except rospy.ROSInterruptException:
    pass