//输出流控制：遍历BHPN节点，如果可以细化，进行pddl_pub,标记节点等待sub
//如果最后没有可以细化节点，显示并执行。

//receiver 一方面给HostCMD发msgs，另一方面给drawtree提供treenode的格式。
#include "robot_msgs/HostCmdArray.h"
#include "robot_msgs/HostCmd.h"
#include "robot_msgs/Strips_Cmd.h"

#include "pddl_add.hpp"
#include "queue"
#include <behavior_tree.h>
#include "pddl_sub.hpp"

extern std::vector<struct BHPN_Node> planner_output;
robot_msgs::Strips_Cmd strips_cmd;
ros::Publisher strips_pub;
ros::Publisher task_sequnce_pub;
std::vector<ros::Publisher> car_pubs;

#include "my_debug_info.h"
Debug::DebugLogger logger;

//借助重规划生成BHPN,建立children
bool DownwardExpansion(struct BHPN_Node& root,int layer){
    //if received new msg
    struct zmq_output zmq_out=receiver_func();
    if(zmq_out.receive_state)
    {
        // ROS_INFO("Received Msg From zmq. size is: %d",receiver_func().second.size());
        //iterate through output
        for(auto x:zmq_out.planner_output)
        {
            // std::shared_ptr<struct BHPN_Node> temp_ptr(&x);
           std::shared_ptr<struct BHPN_Node> temp_ptr= std::make_shared<struct BHPN_Node>(x);
            x.layer=layer;

            root.children.push_back(temp_ptr);
            // ROS_INFO("Zmq reveied Msg : %s",x.action.c_str());
            ROS_INFO("BHPN:Current Action is :%d",x.action_);
            if(!x.action_type==TaskType::Abstruct)
            //ANCHOR debugger
            for(auto id:x.car_id_)
                ROS_INFO("BHPN  ids: %d",id);
            if(x.action_type==TaskType::Abstruct)
            {
                //pub stripsCMD

                strips_cmd.domain_add.data=Situation_Domain_Address2;
                strips_cmd.problem_add.data=Situation_Problem_Address2;

                strips_pub.publish(strips_cmd);
                ROS_INFO("Downward Planning");
                //等待接收到命令,递归处理
                while(!DownwardExpansion(*temp_ptr,layer+1));   //这里不能用x，得用*temp_ptr,因为x生命周期只在这个函数内，传不出去
                
            }
        }
        ROS_INFO("Children.size : %d",root.children.size());
        return true;
    }
    else
        return false;
}

void BHPN2TaskSequence(struct BHPN_Node& root,robot_msgs::HostCmdArray& task_sequence){
    ROS_INFO("In Trans Function");
    ROS_INFO("Trans:Children.size : %d",root.children.size());
    for(auto node_ptr:root.children)
    {
        //如果是抽象动作，向下细化到可执行动作
        if(node_ptr->action_type==TaskType::Abstruct)
        {
            BHPN2TaskSequence(*node_ptr, task_sequence);
            continue;
        }

        robot_msgs::HostCmd temp_task;
        // ROS_INFO("Current Action is :%d",node_ptr->action_);
        //目前只能处理实现了的功能
        if(node_ptr->action_!=TaskIndividual::Unfinished)
        {
            temp_task.mission.mission=node_ptr->action_;
            //ANCHOR debugger
            for(auto id:node_ptr->car_id_)
                ROS_INFO("TS:car_ids: %d",id);
            temp_task.car_id.assign(node_ptr->car_id_.begin(),node_ptr->car_id_.end()); //FIXME   bug with car_id

            temp_task.goal.assign(node_ptr->goals.begin(),node_ptr->goals.end());
            task_sequence.host_cmd_array.push_back(temp_task);
        }

    }
}

void PubTaskSequnce(robot_msgs::HostCmdArray &task_sequnce){
    task_sequnce_pub.publish(task_sequnce);
    for(auto pub:car_pubs)
        pub.publish(task_sequnce);
}

//TODO display not complete debugging.
void BHPN2BTNode(struct BHPN_Node& root, BT::SequenceNode* Root){

    char index='0';
    for(auto node_ptr:root.children)//CBT格式
    {
        index++;
        BT::SequenceNode* sequence = new BT::SequenceNode("sequence "+index);
        BT::ActionNode* action_node = new BT::ActionNode(node_ptr->action);

        std::string temp_str="";
        for(auto str:node_ptr->precondition)
            temp_str+=str+"\n";
        if(temp_str[temp_str.length()-1]=='\n')
            temp_str.pop_back();
        BT::ConditionNode* condition_node = new BT::ConditionNode(temp_str);

        Root->AddChild(sequence);
            sequence->AddChild(condition_node);
            if(node_ptr->action_type==TaskType::Abstruct)
            {
                //再加一个sequence_node，然后从这个sequence_node向下细化
                index++;
                BT::SequenceNode* sequence_ = new BT::SequenceNode("sequence "+index);
                sequence->AddChild(sequence_);
                //递归
                BHPN2BTNode(*node_ptr,sequence_);
            }
            else
            sequence->AddChild(action_node);
    }

}

BT::SequenceNode* dump_bt=new BT::SequenceNode("Display_Behavior_Tree");

void Execute( int TickPeriod_milliseconds)
{
    std::cout << "Start Drawing!" << std::endl;
    // Starts in another thread the drawing of the BT
    std::thread t2(&drawTree, dump_bt);
    t2.detach();
}

int main(int argc, char** argv){

    ros::init(argc,argv,"receiverBHPN");
    ros::NodeHandle nh;

    //initialize
    int total_car_number;
    nh.param("/total_car_number",total_car_number,4);
    std::string simulator;
    nh.getParam("simulator",simulator);

    for(int i = 0 ; i < total_car_number ; i++){
            std::string topic_name;
            
        if(simulator=="stage")
        {
            topic_name= "/robot_" + std::to_string(i) + "/host_cmd";
            ROS_INFO("In Stage,the topic name is :%s!",topic_name);
        }
        else
            if(simulator=="gazebo")
            {
                topic_name = "/robot" + std::to_string(i+1) + "/host_cmd";
                ROS_INFO("In Gazebo,the topic name is :%s!",topic_name);
            }

        ros::Publisher pub = nh.advertise<robot_msgs::HostCmdArray>(topic_name,10);
        car_pubs.push_back(pub);
    }

    strips_pub=nh.advertise<robot_msgs::Strips_Cmd>("/strips_cmd",10);
    task_sequnce_pub=nh.advertise<robot_msgs::HostCmdArray>("/host_cmd",10);

    ros::Rate loop(20);
    int TickPeriod_milliseconds = 1000;

    bool first_=true;

    while(ros::ok()){
        //循环去检测pddl_reveive是否收到消息
        struct BHPN_Node dumb;

        int layer=0;
        //处理得到一整个BHPN
        bool new_=DownwardExpansion(dumb,layer);


        if(new_)
        {
            //debug:
            // ROS_INFO("Children.size : %d",dumb.children.size());
            // for(auto node_ptr:dumb.children)
            // {
            //     ROS_INFO("OUT Msg : %s",node_ptr->action.c_str());
            //     ROS_INFO("OUT Current Action is :%d",node_ptr->action_);
            //     ROS_INFO("OUT children size is :%d",node_ptr->children.size());
            // }
            //
            ROS_INFO("Msg Processing");
            //BHPN转化成HostCmd并发出.
            robot_msgs::HostCmdArray task_sequence;
            BHPN2TaskSequence(dumb,task_sequence);

            
            ROS_INFO("Task Set");
            
            PubTaskSequnce(task_sequence);
            
            ROS_INFO("Task Pub");

            //BHPN转化成BTNode并显示

            //可以用这种方式重新初始化吗
            // dump_bt = new BT::SequenceNode("Display_Behavior_Tree");
            dump_bt->RemoveAllChildren();//draw 允许重新画吗
            BHPN2BTNode(dumb,dump_bt);
            
            //只在第一次调用openGL，之后利用回调直接修改root即可
            if(first_)
            {
                first_=false;
                Execute(TickPeriod_milliseconds);  
            }

        }


        ros::spinOnce();

        loop.sleep();

    }
    return 0;
}


