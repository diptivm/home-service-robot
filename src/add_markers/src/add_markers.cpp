#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "math.h"

int robot_state = 0; //0: start 1: reached pick-up 2: reached drop-off

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

void amclEventCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
  //ROS_INFO("I heard %f", msg->pose.pose.position.y);
  double x_p = 5.0;
  double y_p = 7.0;
  double x_d = 4.0;
  double y_d = 5.0;
  double x = msg->pose.pose.position.x;
  double y = msg->pose.pose.position.y;
  double tolerance = 0.25;
  if((robot_state != 1) && (fabs(x - x_p) < tolerance) && (fabs(y - y_p) < tolerance)) {
    robot_state = 1;
    ROS_INFO("Robot reached pick up");  
    ROS_INFO("Deleting marker");
    //ROS_INFO("%f", fabs(x - x_p));
    //ROS_INFO("%f", fabs(y - y_p));
    marker.color.a = 0.0;
    marker_pub.publish(marker); 
  }
  if((robot_state != 2) && (fabs(x - x_d) < tolerance) && (fabs(y - y_d) < tolerance)) {
    robot_state = 2;
    ROS_INFO("Robot reached drop-off");  
    ROS_INFO("Transporting marker");
    marker.pose.position.x = 4.0;
    marker.pose.position.y = 5.0;
    //ROS_INFO("%f", fabs(x - x_d));
    //ROS_INFO("%f", fabs(y - y_d));
    marker.color.a = 1.0;
    marker_pub.publish(marker);
    ROS_INFO("Reached");
  }
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);

  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);  
  ros::Subscriber sub = n.subscribe("amcl_pose", 1000, amclEventCallback);


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
   

    marker.pose.position.x = 5.0;
    marker.pose.position.y = 7.0;  
    marker.color.a = 1.0; 
    marker_pub.publish(marker);
    ROS_INFO("Placing marker");
    
    ros::spin();

}
