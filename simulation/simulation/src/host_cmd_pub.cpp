#include "ros/ros.h"
#include "robot_msgs/HostCmdArray.h"
#include "robot_msgs/Strips_Cmd.h"
#include "tf/tf.h"
#include <thread>
#include <vector>
#include "ros/package.h"

const std::string Default_Domain_Address0 = ros::package::getPath("zmq_node")+"/../zmq_test/examples/NCS_new/domain.txt";
const std::string Default_Problem_Address0 =  ros::package::getPath("zmq_node")+"/../zmq_test/examples/NCS_new/problem.txt";
const std::string Default_Domain_Address1 = ros::package::getPath("zmq_node")+"/../zmq_test/examples/FetchMoveAndPlace/domain.txt";
const std::string Default_Problem_Address1 =  ros::package::getPath("zmq_node")+"/../zmq_test/examples/NCS_new/FetchMoveAndPlace/problem.txt";
void Command();
void GetMission(robot_msgs::HostCmd &cmd, int mission);
void SetId(robot_msgs::HostCmd &cmd);
struct RosPubs{
    RosPubs(int total_car_number){
        ros::NodeHandle nh;
        std::string simulator;
        std::string topic_name;

        nh.getParam("simulator",simulator);
        
        for(int i=0; i < total_car_number ; i++){
            if(simulator=="stage")
                 topic_name= "/robot_" + std::to_string(i) + "/host_cmd";
            else  
                if(simulator=="gazebo")
                    topic_name = "/robot" + std::to_string(i+1) + "/host_cmd";
            ros::Publisher pub = nh.advertise<robot_msgs::HostCmdArray>(topic_name,10);
            pubs.push_back(pub);
        }
        ros::Publisher pub = nh.advertise<robot_msgs::HostCmdArray>("/host_cmd",10);
        pubs.push_back(pub);
    }
    std::vector<ros::Publisher> pubs;
};
robot_msgs::HostCmdArray host_cmd_array;
//flags:
bool new_cmd{false};
enum Cmd_Type{Host_Cmd,Strips_Cmd};
Cmd_Type cmd_type;

char command = '0';

struct STRIPS_Pub{
    STRIPS_Pub(){
    ros::NodeHandle nh;
     pub = nh.advertise<robot_msgs::Strips_Cmd>("/strips_cmd",10);
    }

    ros::Publisher pub;
};
robot_msgs::Strips_Cmd strips_cmd;

void PDDL_planner_init(){
std::cout<<"please input the path of Domain.txt('0' for Default)"<<std::endl;
std::string temp_add;
std::cin>>temp_add;
if(temp_add=="0")
    strips_cmd.domain_add.data=Default_Domain_Address0;
else
if(temp_add=="1")
    strips_cmd.domain_add.data=Default_Domain_Address1;
else
    {
        ROS_INFO("Warning:text is not default!");
        strips_cmd.domain_add.data=temp_add;
    }

std::cout<<"please input the path of Problem.txt('0' for Default)"<<std::endl;
std::cin>>temp_add;
if(temp_add=="0")
    strips_cmd.problem_add.data=Default_Problem_Address0;
else
if(temp_add=="1")
    strips_cmd.domain_add.data=Default_Problem_Address1;
else
    {
        ROS_INFO("Warning:text is not default!");
        strips_cmd.problem_add.data=temp_add;
    }
}

void SelectMission(){
    robot_msgs::HostCmd host_cmd;
    switch(command){
        case '1':{GetMission(host_cmd,1);break;}
        case '2':{GetMission(host_cmd,2);break;}
        case '3':{GetMission(host_cmd,3);break;}
        case '4':{GetMission(host_cmd,4);break;}
        case '5':{GetMission(host_cmd,5);break;}                
        case '6':{ host_cmd.mission.mission = host_cmd.mission.STOP;break;}
        case '7':{ host_cmd.mission.mission = host_cmd.mission.pause;break;}
        case '8':{ host_cmd.mission.mission = host_cmd.mission.resume;break;}
        case '9':{
            int n;
            std::cout << "--please input task number--" << std::endl;
            std::cin >> n;
            for(int i = 1; i <= n; i++){
                Command();
                SelectMission();
            }
            return ;
        }
        case '0':{
            //display_init();//??????display???action?????????PDDL???tree_node_array(msg)???robot_i???CurrentTask
            PDDL_planner_init();//??????domain.txt???problem.txt??????node.js
            return;
        }
        default:break;
    }
    SetId(host_cmd);
    host_cmd_array.host_cmd_array.push_back(host_cmd);

}

void SetId(robot_msgs::HostCmd &cmd){
    std::cout << "--please input car id--" << std::endl;
    std::string id;
    std::cin >> id;
    for(auto i:id){
        cmd.car_id.push_back(i-48);
    }
}

void GetMission(robot_msgs::HostCmd &cmd, int mission){
    double yaw = 3.14;
    if(mission==1||mission==2||mission==5)
    {
        geometry_msgs::PoseStamped goal;
        std::cout << "please input x :" << std::endl;
        std::cin >> goal.pose.position.x;
        std::cout << "please input y :" << std::endl;
        std::cin >> goal.pose.position.y;
        std::cout << "please input yaw :" << std::endl;
        std::cin >> yaw;
        goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        goal.pose.position.z = 0;
        cmd.goal.push_back(goal);
        cmd.mission.mission = mission;
    }else if(mission==3)
    {
        geometry_msgs::PoseStamped goal;
        yaw = 0;
        //stage????????????

        // goal.pose.position.x = 3;
        // goal.pose.position.y = 15;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // cmd.goal.push_back(goal);

        // goal.pose.position.x = 22;
        // goal.pose.position.y = 15;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // cmd.goal.push_back(goal);

        // goal.pose.position.x = 3;
        // goal.pose.position.y = 6;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // cmd.goal.push_back(goal);

        // goal.pose.position.x = 22;
        // goal.pose.position.y = 6;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // cmd.goal.push_back(goal);

        // NCS????????????

        goal.pose.position.x = 96;
        goal.pose.position.y = -20;
        goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        cmd.goal.push_back(goal);

        goal.pose.position.x = 96;
        goal.pose.position.y = -34;
        goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        cmd.goal.push_back(goal);

        goal.pose.position.x = 112;
        goal.pose.position.y = -20;
        goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        cmd.goal.push_back(goal);

        goal.pose.position.x = 112;
        goal.pose.position.y = -34;
        goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        cmd.goal.push_back(goal);

        // geometry_msgs::PoseStamped goal;
        // std::cout << "please input first x :" << std::endl;
        // std::cin >> goal.pose.position.x;
        // std::cout << "please input first y :" << std::endl;
        // std::cin >> goal.pose.position.y;
        // std::cout << "please input first yaw :" << std::endl;
        // std::cin >> yaw;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // goal.pose.position.z = 0;
        // cmd.goal.push_back(goal);


        // std::cout << "please input second x :" << std::endl;
        // std::cin >> goal.pose.position.xcmd_type;
        // std::cout << "please input second y :" << std::endl;
        // std::cin >> goal.pose.position.y;
        // std::cout << "please input second yaw :" << std::endl;
        // std::cin >> yaw;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // goal.pose.position.z = 0;
        // cmd.goal.push_back(goal);


        // std::cout << "please input third x :" << std::endl;
        // std::cin >> goal.pose.position.x;
        // std::cout << "please input third y :" << std::endl;
        // std::cin >> goal.pose.position.y;
        // std::cout << "please input third yaw :" << std::endl;
        // std::cin >> yaw;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // goal.pose.position.z = 0;
        // cmd.goal.push_back(goal);


        // std::cout << "please input fourth x :" << std::endl;
        // std::cin >> goal.pose.position.x;
        // std::cout << "please input fourth y :" << std::endl;
        // std::cin >> goal.pose.position.y;
        // std::cout << "please input fourth yaw :" << std::endl;
        // std::cin >> yaw;
        // goal.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);
        // goal.pose.position.z = 0;
        // cmd.goal.push_back(goal);
        
        cmd.mission.mission =  mission;
    }
    else if(mission==4){
        cmd.mission.mission = mission;
    }

}


void MissionPub(RosPubs &ros_pubs){
    for(auto pub:ros_pubs.pubs){
        pub.publish(host_cmd_array);
    }
}

void Command(){
    while(ros::ok()){
        std::cout   << "-----------------please input command-----------------" << std::endl
                    << "                1 :  march gps   mission              "  << std::endl
                    << "                2 :  march laser mission              "  << std::endl
                    << "                3 :  search mission                   "  << std::endl
                    << "                4 :  Remote_Control                   "  << std::endl
                    << "                5 :  build up mission                 "  << std::endl
                    << "                6 :  system stand by                  "  << std::endl
                    << "                7 :  mission pause                    "  << std::endl
                    << "                8 :  mission resume                   "  << std::endl
                    << "                9 :  multi mission                    "  << std::endl
                    << "                0 :  PDDL planner                    "  << std::endl;                    
        std::cin  >> command;
        if(command != '1' && command != '2' && command != '3' && command != '4' && command != '5' && command != '6'&& command != '7'&& command != '8'&& command != '9' && command != '0'){
            std::cout << "---input wrong!!  please input again!!!---" << std::endl;
            std::cout << std::endl;
        }else
        {
            new_cmd = true;

            if(command != '0')
                cmd_type=Cmd_Type::Host_Cmd;
            else
                cmd_type=Cmd_Type::Strips_Cmd;
            break;
        }
    }
}

int main(int argc, char **argv){
    ros::init(argc,argv,"host_cmd_pub_node");
    ros::NodeHandle nh;
    int total_car_number;
    nh.param("/total_car_number",total_car_number,4);
    RosPubs ros_pubs(total_car_number);
    STRIPS_Pub strips_pub;

    ros::Rate loop(10);
    while(ros::ok()){
        ros::spinOnce();
        Command();
        if(new_cmd){
            SelectMission();
            if(cmd_type==Cmd_Type::Host_Cmd)
                MissionPub(ros_pubs);
            else
            {
                strips_pub.pub.publish(strips_cmd);
                ROS_INFO("Strips CMD published!!!");
            }

            new_cmd = false;
            std::cout << "                TASK SET!!!" << std::endl;
            std::cout << std::endl;
            host_cmd_array.host_cmd_array.clear();
        }
        loop.sleep();
    }
    
    return 0;
}