#!/bin/sh
xterm  -e  " source develop/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  "  source develop/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" & 
sleep 5
xterm  -e  " source develop/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm  -e  " source develop/setup.bash; rosrun keyboard_teleop keyboard_teleop.py " &
sleep 5