//本程序目的：将传感器原始数据中提取出语义表示，包括：集结、编队可通过性语义;判断是否需要进行重规划，需要时自动提请重规划
//KB的内容应该指示三件事：(1)如何从感知数据中准确获得语义(2)谓词关系如何——不确定性描述、推理与规划问题中(3)动作描述如何
//inference在percption发送数据后回调判断，update_problem和need_replan在环境变化时执行
#include <iostream>
#include <fstream>
#include <map>
#include <ros/ros.h>
#include "robot_msgs/Semantics.h"
#include "robot_msgs/Strips_Cmd.h"

#include "update_problem.hpp"//更新pddl描述头文件


//只表达可能会改变的谓词对应的语义
struct semantics
{
bool Assemble_Passability=false;
bool March_Passability=false;
bool blocked=false;

bool PDDL_ERROR=false;//表示pddl语法是否有误
};

class Inference{

    public:Inference();
    //感知信息的sub
    public:void SemanticsCallback(const robot_msgs::SemanticsConstPtr &msg);
    public:ros::Subscriber Semantics_sub;
    //重规划命令下达pub
    public:ros::Publisher strips_cmd_pub;

    //与感知交互的参数
    public:float min_interval;
    public:float Blocking_probability;
    public:std::string former_semantics_state;

    //高层语义
    struct semantics Inference_semantics;
    //读写文件地址
    std::string pddl_address;

    //处理函数
    struct semantics semantics_extraction();
    std::string semantics2string(struct semantics seman);
    struct semantics string2semantics(std::string seman_str);
    bool semantics_diff(struct semantics semantics_former,struct semantics semantics_now);
    void Ask4Replan();
};

Inference::Inference()
{
    ros::NodeHandle nh;
    Semantics_sub = nh.subscribe("/Semantics",10,&Inference::SemanticsCallback,this);
    strips_cmd_pub  = nh.advertise<robot_msgs::Strips_Cmd>("/strips_cmd",10);
    pddl_address="../../../zmq_test/examples/generated_test/domain.txt";
}



void Inference::SemanticsCallback(const robot_msgs::SemanticsConstPtr &msg)
{
    Inference::Blocking_probability=msg->Blocking_Probability;
    Inference::min_interval=msg->min_interval;
}


struct semantics Inference::semantics_extraction(){//之后归入KB节点,派生谓词关系是否可以用KB的不确定推理来做

    struct semantics new_semantics;

    // simplest semantics_extraction
    if(min_interval>7)
        new_semantics.Assemble_Passability=true;
    if(min_interval>2)
        new_semantics.March_Passability=true;
    if(Blocking_probability>0.7)
        new_semantics.blocked=true;

    //predication and reasoning(Lacking)

    return new_semantics;
}

std::string Inference::semantics2string(struct semantics seman){
    std::string return_str;
    //以下是环境变化也不会影响的固定谓词，可以视为与basic_description同等地位
    std::string basic_description = "(:init(and (car c1)(car c2)(block b1)(location entry)(location destination)";//对象实例化内容，每一个任务的实例化是一定的
    return_str+=basic_description+"(Passability-A entry)";

    if(seman.Assemble_Passability)
        return_str+="(Passability-A destination)";
    if(seman.March_Passability)
        return_str+="(Passability-M destination)";
    if(seman.blocked)
        return_str+="(blocked b1)";
    return_str+="))\n";
    return return_str;
}
//从语义字符串中得到语义信息
struct semantics string2semantics(std::string seman_str){
    struct semantics seman;
    int index=0;
    std::vector<std::string> seman_sub_strs;

    while(seman_str[index]!=' ')//清除空格
    {
        index++;
    }
    if(seman_str.substr(index,10)!="(:init(and")//确定起始位
    {
        ROS_INFO("ERROR in PDDL format:Start bits Error!!!");
        seman.PDDL_ERROR=true;
        return seman;
    }
    index+=10;
    while(1)
    {
        if(seman_str[index]==' ')//清除括号外空格
            {
                index++;
                continue;
            }
        else if(seman_str[index]=='(')//左括号为标志位
        {
            int index_end=index;
            std::string temp_str;
            while(seman_str[index_end++]!=')')
            {
                if(index_end+1>seman_str.size())//不存在对应右括号的报错处理
                {
                    ROS_INFO("ERROR in PDDL format:Missing right bracket!!!");
                    seman.PDDL_ERROR=true;
                    return seman;
                }
            }
            temp_str=seman_str.substr(index,index_end-1);
            seman_sub_strs.push_back(temp_str);

            index=index_end;
        }
        else if(seman_str[index]==')')//右括号表示结束
        {
            break;//while(1)的正常退出条件
        }
    }

    for(auto str:seman_sub_strs){
        if(str[0]=='(')//再次判断一下，是否有错误
        {
            if(str.substr(1,25)=="Passability-A destination")
                seman.Assemble_Passability=true;
            if(str.substr(1,25)=="Passability-M destination")
                seman.March_Passability=true;
            if(str.substr(1,7)=="blocked")
                seman.blocked=true;
        }
        else
        {
            ROS_INFO("ERROR in Sub_strs Abstraction!!!");
            seman.PDDL_ERROR=true;
            return seman;
        }
    }

    return seman;
 }


bool Inference::semantics_diff(struct semantics semantics_former,struct semantics semantics_now){
    if(semantics_former.Assemble_Passability!=semantics_now.Assemble_Passability)
        return true;
    if(semantics_former.March_Passability!=semantics_now.March_Passability)
        return true;
    if(semantics_former.blocked!=semantics_now.blocked)
        return true;
    return false;
}


void Inference::Ask4Replan(){
    robot_msgs::Strips_Cmd strips_cmd;
    strips_cmd.domain_add.data=pddl_address;
    strips_cmd.problem_add.data=pddl_address;
    strips_cmd_pub.publish(strips_cmd);
}



Inference* InferenceAgent;


int main(int argc,char **argv){
    bool Task_Running=true;//从decision_node那判断程序执行情况(暂时简单起见只考虑环境动态变化的不确定性，所以设running=true)
    struct semantics new_semantics,last_semantics,expected_effect;
    std::string new_state_description,last_state_description;

    ros::init(argc, argv, "inference_node");
    ros::NodeHandle nh;
    ros::Rate loop(20);

    while(ros::ok())
    {
        new_semantics=InferenceAgent->semantics_extraction();
        new_state_description=InferenceAgent->semantics2string(new_semantics);

        last_state_description=Read_Problem(InferenceAgent->pddl_address);
        last_semantics=InferenceAgent->string2semantics(last_state_description);
        //并行动作怎么办？分布式动作发生
        //
        //

        //动作运行中状态改变需要重规划OR动作运行结果与预期结果不同需要重规划~可以在重规划可解决的范围内解决动作效果不确定、运行中的环境变化
        if(Task_Running&&InferenceAgent->semantics_diff(last_semantics,new_semantics)|| (!Task_Running&&InferenceAgent->semantics_diff(expected_effect,new_semantics))){
            Write_Problem(InferenceAgent->pddl_address,new_state_description);
            InferenceAgent->Ask4Replan();
        }

        last_semantics=new_semantics;

        ros::spinOnce();
		loop.sleep();
    }

    return 0;
}
