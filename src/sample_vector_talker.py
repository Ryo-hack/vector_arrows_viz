#!/usr/bin/env python
from math import cos
import rospy
import rosparam
from geometry_msgs.msg import Vector3
import math as m
pi = m.pi

def talker():
    rospy.init_node('sample_vector_talker')
    #word = rospy.get_param("~content", "default")
    a = 1
    pub = rospy.Publisher('vector',  Vector3, queue_size=10)
    vector = Vector3()
    r = rospy.Rate(100) # 10hz

    if a == 0:
        for i in range(3600):
            j=m.sin(i*(pi/180))
            x=m.tan(i*(pi/180))
            vector.x= 100*(j/2)*m.sin(i*(pi/180))
            vector.y=10*(x/2)*m.sin(i*(pi/180))
            vector.z= -100*(x/2)*m.cos(i*(pi/180))
            rospy.loginfo(vector)
            pub.publish(vector)
            r.sleep()
    else :
        for i in range(3600):
            vector.x= 0
            vector.y=0
            vector.z= 0
            rospy.loginfo(vector)
            pub.publish(vector)
            r.sleep()



if __name__ == '__main__':
    try:
    
        talker()
    except rospy.ROSInterruptException: pass
