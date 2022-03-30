#ifndef UPDATE_PROBLEM 
#define UPDATE_PROBLEM

#include <fstream>
#include <iostream>
#include <vector>
#include "ros/ros.h"

std::string Read_Problem(std::string pddl_address);
bool Write_Problem(std::string pddl_address,std::string state_description);

#endif