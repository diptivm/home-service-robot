#!/bin/sh
xterm  -e  "source ../../devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/../map/Georgia_studio.world" & 
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/../map/map.yaml" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" 


