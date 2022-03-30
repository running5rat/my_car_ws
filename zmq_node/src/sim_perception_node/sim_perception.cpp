//sim_perception节点利用apriltag中的id，模拟感知得到的语义信息，如果语义信息与当前状态不同，将语义编码为PDDL，发给规划器。
//sim_perception上游是libraries/apriltag_ros/continuous_detection信息
//sim_perception pddl_planner，负责发送给规划器PDDL文件


//percption是实时的，一直发送数据
#include "sim_perception.hpp"

sim_perception::sim_perception(){
    ros::NodeHandle nh;
    //apriltag msg CB
    tag_detection_sub=nh.subscribe("/tag_detections",10,&sim_perception::TagDetectionsCallback,this);
    strips_pub=nh.advertise<robot_msgs::Strips_Cmd>("/strips_cmd",10);



}

sim_perception::~sim_perception()
{

}


void sim_perception::TagDetectionsCallback(const apriltag_ros::AprilTagDetectionArrayConstPtr &msg ){
    if(msg->detections.size()!=0){
        tag_pose=msg->detections[0].pose.pose.pose;
        tag_id=msg->detections[0].id;
    }
    else
    {
        std::vector<int>().swap(tag_id);
    }

}


int main(int argc,char ** argv){

    ros::init(argc, argv, "inference_node");
    ros::NodeHandle nh;
    ros::Rate loop(20);
    sim_perception sim_perception_agent;
    int last_id=-1;

    while(ros::ok())
    {
        if(!sim_perception_agent.tag_id.empty())
        {
            
            if(last_id!=sim_perception_agent.tag_id[0])//确保相同的只发送一遍
            {
                //输入预置的pddl文件
                sim_perception_agent.strips_cmd.domain_add.data=Situation_Domain_Address1;
                sim_perception_agent.strips_cmd.problem_add.data=Situation_Problem_Address1;

                //发送规划请求
                sim_perception_agent.strips_pub.publish(sim_perception_agent.strips_cmd);
            }

            last_id=sim_perception_agent.tag_id[0];

        }




        ros::spinOnce();
        loop.sleep();
    }

    return 1;
}

