#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

float pick[3] = {-0.32, -2.04, 1};
float drop[3] = {-4.15, -1.86, 1};
//char display[2][5] = {"Reached Pick Up Position", "Reached Drop Position"};
int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

    
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = pick[0];
  goal.target_pose.pose.position.y = pick[1];
  goal.target_pose.pose.orientation.w = pick[2];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
  	ROS_INFO("Reached 1st position" );
    ros::Duration(5.0).sleep();
  	goal.target_pose.pose.position.x = drop[0];
  	goal.target_pose.pose.position.y = drop[1];
  	goal.target_pose.pose.orientation.w = drop[2];

   // Send the goal position and orientation for the robot to reach
  	ROS_INFO("Sending goal");
  	ac.sendGoal(goal);

  // Wait an infinite time for the results
  	ac.waitForResult();

  // Check if the robot reached its goal
  	if(ac.getState() ==actionlib::SimpleClientGoalState::SUCCEEDED)
  	{
    	ROS_INFO("Reached Second Position");
    }
    else
    {
    	ROS_INFO("The base failed to move to second location");
    }
    
  }
  else
  {
  	ROS_INFO("The base failed to move. Stupid base.");
  }


  return 0;
}