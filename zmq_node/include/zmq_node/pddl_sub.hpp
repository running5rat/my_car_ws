#ifndef PDDL_SUB
#define PDDL_SUB


//receiver 一方面给HostCMD发msgs，另一方面给drawtree提供treenode的格式。

//third party lib
#include "jsoncpp/json/json.h"
#include "tf/tf.h"


#define OBSTACLE_LOC_X        -8
#define OBSTACLE_LOC_Y        2.3
#define UNLOAD_LOC_X            -15.7
#define UNLOAD_LOC_Y           -4.3
#define ENTRY_LOC_X               -13.6
#define ENTRY_LOC_Y                2.3
#define DESTINATION_LOC_X 1.5
#define DESTINATION_LOC_Y 2.3

 enum TaskIndividual
{
	NonTask,
	March_gps,
	March_laser,
	Search,
	Remote_Control,
	Assemble,
	Stop,
	Pause,
	Resume,
    Unfinished,
};

enum TaskType
{
    Concrete,
    Abstruct,
};

enum Locations
{
	Entry,
	Destination,
    Obstacle_site,
    Unload_site,
    Start_site,
};

struct BHPN_Node{
std::vector< std::string> precondition;
std::string action;
std::vector< std::string> effect;
std::vector<std::string> car_id;

TaskType action_type;
TaskIndividual action_;
std::vector<int> car_id_;
std::vector<geometry_msgs::PoseStamped> goals;

unsigned int layer;
std::vector<std::shared_ptr<BHPN_Node>> children;
// std::vector<BHPN_Node*> children;
};

struct zmq_output{
    bool receive_state;
    std::vector<struct BHPN_Node> planner_output;
};

Json::Value string2json(std::string &msg);
std::vector<geometry_msgs::PoseStamped> MapFromLocation2Pose(std::string location);
zmq_output receiver_func(void);
void Json2BHPN(Json::Value json);

#endif