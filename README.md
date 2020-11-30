# home-service-robot
## Summary
Simulated application using ros and gazebo for a mobile turtlebot autonomously navigating an indoor enviornment and performing a pick-place task. The object to be picked is a ball represented as a marker on RViz. Requires a 2D occupancy-grid map (in the form of a pgm image) of the environment. 
## Implementation
1. Gazebo world models an indoor enviornment and spawns a differential drive turtlebot equipped with a LIDAR and RGB camera. 
2. The map in this project was created using RTAB-map, using a Graph-SLAM technique on 2D-LIDAR and RGBD camera data, on a different robot. It can also be created using grid-based SLAM techniques such as FAST SLAM, and using the same turtlebot. 
3. The ros amcl package (with special configurations for the turtlebot) is used for the robot localization, path planning using local and global cost planners, and for sending locomotion commands to move the robot base.
4. A separate node (pcik_objects) commands the robot to navigate to the object's pick-up location, wait a while to pick the object, and then navigate to transport it to the drop-off.
5. Finally, to simulate the picking and dropping of the object (a white ball), a representative marker is added to the RViz visualization, and made to disappear and appear at the drop off as the robot completes its pick and place mission. 
## Usage
1. Run <code> catkin_make </code> in the project directory to make this your catkin workspace.
2. Launch the shell script file 
<code> ./home_service.sh </code>. 
3. Note, if Gazebo fails to launch, one may be need to install rospkg as a missing dependency.<code> pip install rospkg </code>. 
4. Observe the simulated robot's movement in gazebo and visualize the pick and place task progress in RViz.
## Improvements
1. Accepting user input for a variable drop off location within the house.

