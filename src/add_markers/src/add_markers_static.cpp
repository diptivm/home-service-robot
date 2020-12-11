#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "math.h"

ros::Publisher marker_pub;
visualization_msgs::Marker marker;


int main( int argc, char** argv )
{
  
  double x_p = 4.5;
  double y_p = -0.5;
  double x_d = 4.0;
  double y_d = 5.0;   

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);

  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);  


    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::SPHERE;;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 1.0f;
    marker.color.b = 1.0f;


    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
   

    marker.pose.position.x = x_p;
    marker.pose.position.y = y_p;  
    marker.color.a = 1.0; 
    marker_pub.publish(marker);
    ROS_INFO("Placing marker");

    ros::Duration(5).sleep();

    ROS_INFO("Deleting marker");
    marker.color.a = 0.0;
    marker_pub.publish(marker);

    ros::Duration(5).sleep();

    ROS_INFO("Transporting marker");
    marker.pose.position.x = x_d;
    marker.pose.position.y = y_d;
    
    marker.color.a = 1.0;
    marker_pub.publish(marker);
    ROS_INFO("Reached");
    
    ros::spin();

}
