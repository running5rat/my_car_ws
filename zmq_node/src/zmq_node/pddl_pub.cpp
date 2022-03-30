//PDDL_Pub需要解决的问题：（1）自动生成状态信息的problem.txt描述（2）决定什么时候重规划——与感知之间形成通路 (3)
//third party lib
#include "jsoncpp/json/json.h"
//ros
#include "std_msgs/String.h"
#include "ros/ros.h"
//my lib
#include "zmq_lib.h"
#include "robot_msgs/Strips_Cmd.h"



class Strips_Cmd{
    public:Strips_Cmd();
    public:void StripsCmdCallback(const robot_msgs::Strips_CmdConstPtr &msg);
    public:ros::Subscriber Strips_Cmd_sub;
    public:std::string domain_add;
    public:std::string problem_add;
    public:bool first_received;
    public:bool new_order=false;
};
Strips_Cmd::Strips_Cmd()
{
        ros::NodeHandle nh;
        Strips_Cmd_sub=nh.subscribe("/strips_cmd",10,&Strips_Cmd::StripsCmdCallback,this);
}
void Strips_Cmd::StripsCmdCallback(const robot_msgs::Strips_CmdConstPtr &msg){

    domain_add=msg->domain_add.data;
    problem_add=msg->problem_add.data;

    new_order=true;
}


std::string fmtMsg(std::string domain_add,std::string problem_add){
        Json::Value msg;
        msg["domain_address"] = domain_add;
        msg["problem_address"] =problem_add ;
        ROS_INFO("%s",msg.toStyledString().c_str());
        return msg.toStyledString();
}



int main(int argc,char **argv)
{
    std::string ip_address="127.0.0.1:2000";

    //ros_init
    ros::init(argc,argv,"publish_robot_state");
    ros::NodeHandle nh;
    ros::Rate loop(20);
    Strips_Cmd strips_cmd;
    //zmq_init
    zmq::context_t ctx(1);
    zmq_lib::Sender sender(ip_address,ctx);

    std::string msgg;
    while(ros::ok())
    {
        if(strips_cmd.new_order)//new_order:人第一次发描述或环境变化需要重新规划
        {
            msgg=fmtMsg(strips_cmd.domain_add,strips_cmd.problem_add);
            sender.sendMsg(msgg);
            strips_cmd.new_order=false;
        }


        ros::spinOnce();
        loop.sleep();
    }

    return 0;
}