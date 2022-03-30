#include <ros/ros.h>
#include "robot_msgs/Strips_Cmd.h"
#include "ros/package.h"
#include "apriltag_ros/AprilTagDetectionArray.h"
#include "pddl_add.hpp"
class sim_perception
{
    public:
	sim_perception();
	virtual ~sim_perception();

    //apriltag sub
	public: std::vector<int> tag_id;
    public:  geometry_msgs::Pose tag_pose;
    public: void TagDetectionsCallback(const apriltag_ros::AprilTagDetectionArrayConstPtr &msg);
    public:ros::Subscriber tag_detection_sub;

    //strips pub
    robot_msgs::Strips_Cmd strips_cmd;
    ros::Publisher strips_pub;
};



