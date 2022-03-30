#include "update_problem.hpp"

std::string Read_Problem(std::string pddl_address){//读出来的是init所在整行

    using namespace std;
    fstream file;
    std::vector<string> cpp_path;
    string description_str;

    cpp_path.push_back(pddl_address);
    file.open(cpp_path[0],ios_base::in | ios_base::out);
    if(!file.is_open()){
        ROS_WARN("problem.txt open failed !!!! ");
        return "Error";
    }

    char buffer[1024];
    string file_content="";
    while(file.getline(buffer,sizeof(buffer)))
    {
        string line_content(buffer);
        line_content += "\n";
        for(int i=0;i<line_content.size();i++)//对每一行匹配init是不是复杂度太高了？
            {
                if(line_content[i]=='i'&&line_content[i+1]=='n'&&line_content[i+2]=='i'&&line_content[i+3]=='t')//目前只需要更改init行,之后blended executing and planning时可能还需要改goal
                {
                    description_str=line_content;
                }
            }
    }

    file.close();
    return description_str;
}


bool Write_Problem(std::string pddl_address,std::string state_description){//state_description是init所在整行

    using namespace std;
    fstream file;
    std::vector<string> cpp_path;

    cpp_path.push_back(pddl_address);
    file.open(cpp_path[0],ios_base::in | ios_base::out);
    if(!file.is_open()){
        ROS_WARN("problem.txt open failed !!!! ");
        return false;
    }

    char buffer[1024];
    string file_content="";
    while(file.getline(buffer,sizeof(buffer)))
    {
        string line_content(buffer);
        line_content += "\n";
        for(int i=0;i<line_content.size();i++)//对每一行匹配init是不是复杂度太高了？
            {
                if(line_content[i]=='i'&&line_content[i+1]=='n'&&line_content[i+2]=='i'&&line_content[i+3]=='t')//目前只需要更改init行,之后blended executing and planning时可能还需要改goal
                {
                    line_content=state_description;
                }
            }


        file_content += line_content;
    }

    file.close();
    file.open(cpp_path[0],ios_base::in|ios_base::out);
    if(file.is_open()){
        file<<file_content;
    }
    file.close();
    return true;
}
