#include "jsoncpp/json/json.h"
#include "iostream"
#include "string.h"
#include "zmq_lib.h"


#define ACTION_TYPE 0
#define CONDITION_TYPE 1
Json::Value string2json(std::string &msg){//从zmq传输格式到json
    Json::Value json;
    Json::Reader reader;
    reader.parse(msg.c_str(),json);
    return json;
}

struct pddl_node
{
std::string precondition;
std::string action;
};



struct ActionMsg{

ActionMsg(std::vector<pddl_node>  &pddl_nodes_){
pddl_nodes=pddl_nodes_;
}

std::string fmtMsg(){
Json::Value msgs;
Json::Value msg;
for(auto pddl_node_:pddl_nodes)
{
    msg["precondition"]=pddl_node_.precondition;
    msg["action"]=pddl_node_.action;
    msgs.append(msg);
}

return msgs.toStyledString();
}


void GetDataFromMsg(Json::Value msgs,std::vector<pddl_node> & task_sequence){
    for(auto pddl_node_:msgs)
    {
        pddl_node temp;
        temp.action=pddl_node_["action"].asString();
        temp.precondition=pddl_node_["precondition"].asString();
        task_sequence .push_back(temp);
    }

}

std::vector<pddl_node> pddl_nodes;
};
