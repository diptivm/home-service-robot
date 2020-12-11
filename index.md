# home-service-robot
## Summary
Simulated application using ros and gazebo for a mobile turtlebot autonomously navigating an indoor enviornment and performing a pick-place task. The object to be picked is a ball represented as a marker on RViz. Employs a 2D occupancy-grid map (in the form of a pgm image) of the environment. 
## Video - using PGM_Map_Creator maps from the /main branch
[![Gazebo simulation](http://img.youtube.com/vi/VTJuzgkDmx0/0.jpg)](https://www.youtube.com/embed/VTJuzgkDmx0
 "Home Service Robot Video - Gazebo")
 [![RViz visualization](http://img.youtube.com/vi/ZwqgDXNuH0M/0.jpg)](https://www.youtube.com/embed/ZwqgDXNuH0M
  "Home Service Robot Video - Rviz")
 ## Video - using gmapping map
[![Gazebo simulation - GMAP](http://img.youtube.com/vi/Y0kl1pGt5ic/0.jpg)]( https://youtu.be/Y0kl1pGt5ic
 "Home Service Robot Video - Gazebo")
  [![RViz visualization - GMAP](http://img.youtube.com/vi/NpJmN15OBjE/0.jpg)](https://www.youtube.com/embed/NpJmN15OBjE
  "Home Service Robot Video - Rviz")

## Implementation
1. Gazebo world models an indoor enviornment and spawns a differential drive turtlebot equipped with a LIDAR and RGB camera. 
2. The map in the main/ branch of this project was created using PGM Map creator (https://github.com/hyfan1116/pgm_map_creator), which creates a pgm map of an environment based on its gazebo world file .
3. The map in the gmap/ branch was created using the ros slam_gmapping package implenting grid-based FAST-SLAM on a 2D-LIDAR-equipped robot. Note, the map was post-processed to remove ghost obstacles and fill in some missing boundaries using 'IrfanView' (https://www.irfanview.com/). The original map (located at src/map/pgm-0/map.pgm) can be compared with the edited map (at src/map/pgm/map/pgm) to see the changes.
4. The ros amcl package (with special configurations for the turtlebot) is used for the robot localization, path planning using local and global cost planners, and for sending locomotion commands to move the robot base.
5. A separate node (pick_objects) commands the robot to navigate to the object's pick-up location, wait a while to pick the object, and then navigate to transport it to the drop-off.
5. Finally, to simulate the picking and dropping of the object (a white ball), a representative marker is added to the RViz visualization by the add_markers node, and made to disappear and appear at the drop off as the robot completes its pick and place mission. 
## Usage
1. Run <code> catkin_make </code> in the project directory to make this your catkin workspace.
2. Launch the shell script file 
<code> ./home_service.sh </code>. 
3. Note, if Gazebo fails to launch, one may be need to install rospkg as a missing dependency.<code> pip install rospkg </code>. 
4. Observe the simulated robot's movement in gazebo and visualize the pick and place task progress in RViz.
## Improvements
1. Tuning of gmapping parameters (/slam_gmapping/angularUpdate and /slam_gmapping/linearUpdate) to improve map quality - it can be seen that adjacent walls are separated out at a small angle in the original (unedited) map. 
2. Accepting user input for a variable drop off location within the house.


## Implementation
1. Gazebo world models an indoor enviornment and spawns a differential drive turtlebot equipped with a LIDAR and RGB camera. 
2. The map in this project was created using RTAB-map, using a Graph-SLAM technique on 2D-LIDAR and RGBD camera data, on a different robot. It can also be created using grid-based SLAM techniques such as FAST SLAM, and using the same turtlebot. 
3. The ros amcl package (with special configurations for the turtlebot) is used for the robot localization, path planning using local and global cost planners, and for sending locomotion commands to move the robot base.
4. A separate node (pick_objects) commands the robot to navigate to the object's pick-up location, wait a while to pick the object, and then navigate to transport it to the drop-off.
5. Finally, to simulate the picking and dropping of the object (a white ball), a representative marker is added to the RViz visualization by the add_markers node, and made to disappear and appear at the drop off as the robot completes its pick and place mission. 
## Usage
1. Run <code> catkin_make </code> in the project directory to make this your catkin workspace.
2. Launch the shell script file 
<code> ./home_service.sh </code>. 
3. Note, if Gazebo fails to launch, one may be need to install rospkg as a missing dependency.<code> pip install rospkg </code>. 
4. Observe the simulated robot's movement in gazebo and visualize the pick and place task progress in RViz.
## Improvements
1. Accepting user input for a variable drop off location within the house.

