#!/bin/bash

# Build the catkin_ws
cd $(pwd)/../..; catkin_make

# Launch the nodes
xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/turtlebot_simulator/turtlebot_gazebo/worlds/corridor.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 7
xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/map/map.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5
xterm  -e "source devel/setup.bash; rosrun rviz rviz -d $(pwd)/src/rvizConfig/home_serviceConfig.rviz" &
sleep 15
xterm  -e "source devel/setup.bash; rosrun add_markers add_markers" &
sleep 3
xterm  -e "source devel/setup.bash; rosrun pick_objects pick_objects"