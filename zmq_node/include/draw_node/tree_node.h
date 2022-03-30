#ifndef TREE_NODE_H
#define TREE_NODE_H


#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif

   #define DEBUG  // uncomment this line if you want to print debug messages

#ifdef DEBUG
  // #define DEBUG_STDERR(x) (std::cerr << (x))
#define DEBUG_STDOUT(str) do { std::cout << str << std::endl; } while ( false )  // NOLINT(whitespace/braces)


#else
#define DEBUG_STDOUT(str)
#endif


#include <iostream>
#include <unistd.h>

#include <string>

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

namespace BT
{
// Enumerates the possible types of a node, for drawinf we have do discriminate whoich control node it is:

enum NodeType {ACTION_NODE, CONDITION_NODE, CONTROL_NODE};
enum DrawNodeType {PARALLEL, SELECTOR, SEQUENCE, SEQUENCESTAR, SELECTORSTAR, ACTION, CONDITION, DECORATOR};
// Enumerates the states every node can be in after execution during a particular
// time step:
// - "Success" indicates that the node has completed running during this time step;
// - "Failure" indicates that the node has determined it will not be able to complete
//   its task;
// - "Running" indicates that the node has successfully moved forward during this
//   time step, but the task is not yet complete;
// - "Idle" indicates that the node hasn't run yet.
// - "Halted" indicates that the node has been halted by its father.
enum ReturnStatus {RUNNING, SUCCESS, FAILURE, IDLE, HALTED, EXIT};

// Enumerates the options for when a parallel node is considered to have failed:
// - "FAIL_ON_ONE" indicates that the node will return failure as soon as one of
//   its children fails;
// - "FAIL_ON_ALL" indicates that all of the node's children must fail before it
//   returns failure.
enum FailurePolicy {FAIL_ON_ONE, FAIL_ON_ALL};
enum ResetPolity   {ON_SUCCESS_OR_FAILURE, ON_SUCCESS, ON_FAILURE};

// Enumerates the options for when a parallel node is considered to have succeeded:
// - "SUCCEED_ON_ONE" indicates that the node will return success as soon as one
//   of its children succeeds;
// - "BT::SUCCEED_ON_ALL" indicates that all of the node's children must succeed before
//   it returns success.
enum SuccessPolicy {SUCCEED_ON_ONE, SUCCEED_ON_ALL};

// Tree Nodes
class TreeNode
{
private:
    std::string name_;
    bool has_parent_;

protected:
    bool is_state_updated_;
    ReturnStatus status_;
    ReturnStatus color_status_;
    std::mutex state_mutex_;
    std::mutex color_state_mutex_;
    std::condition_variable state_condition_variable_;
    NodeType type_;
    float x_shift_, x_pose_;

public:
    std::thread thread_;

    explicit TreeNode(std::string name);
    ~TreeNode();
    void SetNodeState(ReturnStatus new_state);
    void set_color_status(ReturnStatus new_color_status);
    ReturnStatus ReadState();
    ReturnStatus get_color_status();
    virtual int DrawType() = 0;
    virtual int Depth() = 0;
    void set_x_pose(float x_pose);
    float get_x_pose();
    void set_x_shift(float x_shift);
    float get_x_shift();
    ReturnStatus get_status();
    void set_status(ReturnStatus new_status);
    std::string get_name();
    void set_name(std::string new_name);
    NodeType get_type();
    bool has_parent();
    void set_has_parent(bool value);
};

//Control Node
class ControlNode : public TreeNode
{
protected:
    std::vector<TreeNode*> children_nodes_;
    std::vector<ReturnStatus> children_states_;
    unsigned int N_of_children_;
    ReturnStatus child_i_status_;

public:
    explicit ControlNode(std::string name);
    ~ControlNode();

    void AddChild(TreeNode* child);

    //ANCHOR add by LXL
    void RemoveAllChildren(void);

    unsigned int GetChildrenNumber();
    std::vector<TreeNode*> GetChildren();

    int Depth();
};

//FallbackNode
class FallbackNode : public ControlNode
{
public:
    explicit FallbackNode(std::string name);
    ~FallbackNode();
    int DrawType();
};

//SequenceNode
class SequenceNode : public ControlNode
{
public:
    explicit SequenceNode(std::string name);
    ~SequenceNode();
    int DrawType();
};

//LeafNode
class LeafNode : public TreeNode
{
protected:
public:
    explicit LeafNode(std::string name);
    ~LeafNode();
    int Depth();
};

//ActionNode
class ActionNode : public LeafNode
{
public:
    // Constructor
    explicit ActionNode(std::string name);
    ~ActionNode();

    int DrawType();
};

//ConditionNode
class ConditionNode : public LeafNode
{
public:
    // Constructor
    explicit ConditionNode(std::string name);
    ~ConditionNode();

    int DrawType();
};

} // namespace BT

#endif//TREE_NODE_H