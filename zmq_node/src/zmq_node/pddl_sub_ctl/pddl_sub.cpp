//PDDL_sub主要任务：（1）解码规划器信息 （2）编码到BHPN格式输出
#include "pddl_sub.hpp"

//ros
#include "std_msgs/String.h"
#include "ros/ros.h"
//my lib
#include "zmq_lib.h"

#include <map>
#include <utility>

//config id & ip
std::string pddl_ip="127.0.0.1:3000";
//zmq_init
zmq::context_t ctx(1);
zmq_lib::Receiver pddl_receive(std::vector<std::string>{pddl_ip},ctx);

//TODO 内卷，启动！！！

std::map<std::string,TaskIndividual>  action_table={
    {"NonTask",TaskIndividual::NonTask},
    {"March",TaskIndividual::March_laser},//目前march就是指效果最好的march(march_laser)
    {"Search",TaskIndividual::Search},
    {"Remote_Control",TaskIndividual::Remote_Control},
    {"Assemble",TaskIndividual::Assemble},//assemble在语义里代表两车集结
    {"Move",TaskIndividual::Assemble},//move是单车集结
    {"Stop",TaskIndividual::Stop},
    {"Pause",TaskIndividual::Pause},
    {"Grab",TaskIndividual::Unfinished},
    {"Unload",TaskIndividual::Unfinished},
    // {"Move-Obstable",TaskIndividual::Abstruct},
};//行为转换表，实际会用的只有Assemble、March、Pause、Stop以后会加入一个抓取与放置两个功能

std::map<std::string,int> id_table={
{"c0",0},
{"c1",1},
{"c2",2},
{"c3",3},
{"c4",4},
{"c5",5},
{"c6",6},
{"c7",7},
{"c8",8},
{"c9",9},
};//自动生成行为树功能只支持最多10个车,(可拓)

std::map<std::string,Locations>location_table={
    {"entry",Entry},
    {"destination",Destination},
    {"Obstableloc",Obstacle_site},
    {"Unloadingloc",Unload_site},
    {"Startloc",Start_site},
};

std::vector<geometry_msgs::PoseStamped> MapFromLocation2Pose(std::string location){
    std::vector<geometry_msgs::PoseStamped> goals;
    geometry_msgs::PoseStamped goal;
    double yaw=0;
    goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
    goal.pose.position.z = 0;

   switch (location_table[location])//string的switch方法：Hash/Map
   {
    //start_loc不参与host_cmd，而且不是一个固定位置，暂不做处理
   case Locations::Start_site:
       break;
//之后要让给定感知
    case Locations::Obstacle_site:
        goal.pose.position.x=OBSTACLE_LOC_X;
        goal.pose.position.y=OBSTACLE_LOC_Y;
       break;

    case Locations::Unload_site:
        goal.pose.position.x=UNLOAD_LOC_X;
        goal.pose.position.y=UNLOAD_LOC_Y;
       break;
   
   case Locations::Entry:
        goal.pose.position.x=ENTRY_LOC_X;
        goal.pose.position.y=ENTRY_LOC_Y;
       break;
    case Locations::Destination:
        goal.pose.position.x=DESTINATION_LOC_X;
        goal.pose.position.y=DESTINATION_LOC_Y;
       break;

   default:
       break;
   }
   goals.push_back(goal);//之前为了兼容多goal的搜索问题，把host_cmd写成带vector::pose了
    return goals;
}

Json::Value string2json(std::string &msg){//从zmq传输格式到json
    Json::Value json;
    Json::Reader reader;
    reader.parse(msg.c_str(),json);
    return json;
}

void Json2BHPN(Json::Value json,std::vector<struct BHPN_Node>& planner_output)
{

    for(int i=0;i<json.size();i++)
    {
        //每次生成新的temp_node,就不用初始化了
        struct BHPN_Node temp_node;
        //display patition
        temp_node.action=json[i]["action"].asString();
        for(int j=0;j<json[i]["precondition"].size();j++)
        {
            if(json[i]["precondition"][j]["operation"]=="not")
                temp_node.precondition.push_back("not "+json[i]["precondition"][j]["action"].asString());
            else
                temp_node.precondition.push_back(json[i]["precondition"][j]["action"].asString());
        }
        for(int j=0;j<json[i]["effect"].size();j++)
            temp_node.effect.push_back(json[i]["effect"][j]["action"].asString());

        //cmd patition
        if(action_table.find(temp_node.action)!=action_table.end())//非抽象节点
        {
            temp_node.action_type=TaskType::Concrete;
            temp_node.action_=action_table[temp_node.action];
            for(int j=0;j<json[i]["parameters"].size();j++)//car_id、block_id和location、port
            {
                if(json[i]["parameters"][j]["type"].asString()=="car")//是车辆信息
                {
                    temp_node.car_id.push_back(json[i]["parameters"][j]["parameter"].asString()); //display partition
                    temp_node.car_id_.push_back(id_table[json[i]["parameters"][j]["parameter"].asString()]);
                }

                if(json[i]["parameters"][j]["type"].asString()=="block")//是障碍物信息
                    ;
                if(json[i]["parameters"][j]["type"].asString()=="location")//是位置信息
                    temp_node.goals=MapFromLocation2Pose(json[i]["parameters"][j]["parameter"].asString());
            }
        }
        else
            temp_node.action_type=TaskType::Abstruct;

        planner_output.push_back(temp_node);
    }
}


struct zmq_output receiver_func(void){

    std::string msg;
    zmq_output output;


    msg.clear();
    //接收信息
    pddl_receive.receiveMsg(msg);
    //信息判空
    if(!msg.empty()){
        //str转json
        ROS_INFO("loc3");
        Json::Value json = string2json(msg);
        ROS_INFO("loc4");
        //json解码到BHPN
        Json2BHPN(json,output.planner_output);
        ROS_INFO("loc5");
        output.receive_state=true;
        return output;
    }
    else
    {
        output.receive_state=false;
        return output;
    }

}

