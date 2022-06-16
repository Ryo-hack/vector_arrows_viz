#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <string>
#include <math.h>
#include <iostream>
#define PI 3.1415926535897932384626


class  marker_arrow_vector{
    private: 
            ros::NodeHandle nh;
            visualization_msgs::Marker marker;
            ros::Subscriber vector_sub;
            ros::Publisher arrow_marker_pub;
            tf::Quaternion quat;
            geometry_msgs::Quaternion geometry_quat;
            double radias,theta,phi;
            double Quaternion [4];
    public:
            marker_arrow_vector();
            void euler_to_quaternion ();
            void  marker_arrow_pub();
            void vector_callback(const geometry_msgs ::Vector3 & Vector);
};  

marker_arrow_vector::marker_arrow_vector(){
    arrow_marker_pub =  nh.advertise<visualization_msgs::Marker>("arrow_pub", 10);
    vector_sub = nh.subscribe("vector", 10, & marker_arrow_vector::vector_callback,this);//parm
    radias=0;theta=0;phi=0;
    Quaternion[0]=0;Quaternion[1]=0;Quaternion[2]=0;Quaternion[3]=0;
};

void marker_arrow_vector::vector_callback(const geometry_msgs ::Vector3 & Vector){
    
    radias = sqrtf(pow(Vector.x,2)+pow(Vector.y,2)+pow(Vector.z,2));
    theta = asin(Vector.y / radias);
    phi = atan2(Vector.z , Vector.x);

    double roll , pitch,  yaw ;
    roll = 0.0 ;
    pitch =phi;
    yaw = theta;

    quat=tf::createQuaternionFromRPY(roll,pitch,yaw);
    quaternionTFToMsg(quat, geometry_quat);

    Quaternion[0]=geometry_quat.x;
    Quaternion[1]=geometry_quat.y;
    Quaternion[2]=geometry_quat.z;
    Quaternion[3]=geometry_quat.w;

}

void marker_arrow_vector::marker_arrow_pub(){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";////parm
        marker.header.stamp = ros::Time::now();
        marker.ns ="arrow_shapes";
        marker.id = 0;

        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;

        marker.pose.orientation.x = Quaternion[0];
        marker.pose.orientation.y = Quaternion[1];
        marker.pose.orientation.z = Quaternion[2];
        marker.pose.orientation.w = Quaternion[3];

        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;

        marker.scale.x = 0.005*radias;
        marker.scale.y = 0.01;
        marker.scale.z = 0.01;

        marker.lifetime = ros::Duration();

        marker.type = 0;

        arrow_marker_pub.publish(marker);

};

int main(int argc, char **argv){
    ros::init(argc, argv, "arrow_viz");
    marker_arrow_vector marker_arrow_vector;
    ros::Rate loop_rate(1000);
    ROS_INFO("arrow_viz");
      while (ros::ok()){
       ros::spinOnce();
       marker_arrow_vector.marker_arrow_pub();
       loop_rate.sleep();
      }
    return 0;
}