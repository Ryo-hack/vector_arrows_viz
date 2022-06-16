#!/usr/bin/env python
from math import cos
from tokenize import Double
import rospy
import rosparam
from geometry_msgs.msg import Vector3
import math as m
pi = m.pi

def talker():
    rospy.init_node('sample_vector_talker')
    #word = rospy.get_param("~content", "default")

    pub = rospy.Publisher('vector',  Vector3, queue_size=10)

    r = rospy.Rate(100) # 10hz
    for i in range(3600):
        vector = Vector3()
        j=i*m.sin(i*(pi/180))
        vector.x= j*m.cos(i*(pi/180))
        vector.y= j*m.cos(i*(pi/180))   
        vector.z= j*m.sin(i*(pi/180))
        rospy.loginfo(vector)
        pub.publish(vector)
        r.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
    