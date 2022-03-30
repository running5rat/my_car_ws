#include <ros/ros.h>
#include "ros/package.h"

//NCS问题
 std::string Situation_Domain_Address0 = ros::package::getPath("zmq_node")+"/../zmq_test/examples/NCS_new/domain.txt";
 std::string Situation_Problem_Address0 =  ros::package::getPath("zmq_node")+"/../zmq_test/examples/NCS_new/problem.txt";
//NAMO问题
std::string Situation_Domain_Address1 = ros::package::getPath("zmq_node")+"/../zmq_test/examples/NavigationAmongMoveableObstacles/domain.txt";
std::string Situation_Problem_Address1 =  ros::package::getPath("zmq_node")+"/../zmq_test/examples/NavigationAmongMoveableObstacles/problem.txt";
//FMAP问题
std::string Situation_Domain_Address2 = ros::package::getPath("zmq_node")+"/../zmq_test/examples/NavigationAmongMoveableObstacles/FetchMoveAndPlace/domain.txt";
std::string Situation_Problem_Address2 =  ros::package::getPath("zmq_node")+"/../zmq_test/examples/NavigationAmongMoveableObstacles/FetchMoveAndPlace/problem.txt";
