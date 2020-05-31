#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
//Define 2-D goal
typedef struct GOALS_2D {float x_pos,y_pos;};

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

  float x_distance[2] = {0.5,-2.5};
  float orientation[2] = {1.0,-1.5};
  GOALS_2D pick_up = {.x_pos=.5,.y_pos=0};
  GOALS_2D drop_off = {.x_pos=-2.5,.y_pos=0};
    
    
    // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  for (int count =0; count < sizeof(x_distance); count++){
  
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x_distance[count];
  goal.target_pose.pose.orientation.w = orientation[count];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to Goal %f ", count);
  else
    ROS_INFO("The base failed to reach the Goal %f for some reason", count);
  
  ros::Duration(5.0).sleep() ;}



  return 0;
}
