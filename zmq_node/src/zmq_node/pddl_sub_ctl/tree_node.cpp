/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <tree_node.h>
#include <string>


BT::TreeNode::TreeNode(std::string name)
{
    // Initialization
    name_ = name;
    has_parent_ = false;
    is_state_updated_ = false;
}

BT::TreeNode::~TreeNode() {}

BT::ReturnStatus BT::TreeNode::get_color_status()
{
    // Lock acquistion
    std::lock_guard<std::mutex> LockGuard(color_state_mutex_);

    return color_status_;
}

float BT::TreeNode::get_x_pose()
{
    return x_pose_;
}

void BT::TreeNode::set_x_pose(float x_pose)
{
    x_pose_ = x_pose;
}


float BT::TreeNode::get_x_shift()
{
    return x_shift_;
}

void BT::TreeNode::set_x_shift(float x_shift)
{
    x_shift_ = x_shift;
}

void BT::TreeNode::set_name(std::string new_name)
{
    name_ = new_name;
}

std::string BT::TreeNode::get_name()
{
    return name_;
}


BT::NodeType BT::TreeNode::get_type()
{
    return type_;
}

bool BT::TreeNode::has_parent()
{
    return has_parent_;
}

void BT::TreeNode::set_has_parent(bool value)
{
    has_parent_ = value;
}

BT::ControlNode::ControlNode(std::string name) : TreeNode::TreeNode(name)
{
    type_ = BT::CONTROL_NODE;
}

BT::ControlNode::~ControlNode() {}

void BT::ControlNode::AddChild(TreeNode* child)
{
    child->set_has_parent(true);
    children_nodes_.push_back(child);
    children_states_.push_back(BT::IDLE);
}

void BT::ControlNode::RemoveAllChildren(void){
children_nodes_.clear();
}

unsigned int BT::ControlNode::GetChildrenNumber()
{
    return children_nodes_.size();
}


std::vector<BT::TreeNode*> BT::ControlNode::GetChildren()
{
    return children_nodes_;
}

int BT::ControlNode::Depth()
{
    int depMax = 0;
    int dep = 0;
    for (unsigned int i = 0; i < children_nodes_.size(); i++)
    {
        dep = (children_nodes_[i]->Depth());
        if (dep > depMax)
        {
            depMax = dep;
        }
    }
    return 1 + depMax;
}

BT::FallbackNode::FallbackNode(std::string name) : ControlNode::ControlNode(name) {}
int BT::FallbackNode::DrawType()
{
    return BT::SELECTOR;
}

BT::SequenceNode::SequenceNode(std::string name) : ControlNode::ControlNode(name) {}
int BT::SequenceNode::DrawType()
{
    return BT::SEQUENCE;
}

BT::LeafNode::LeafNode(std::string name) : TreeNode(name) {}
int BT::LeafNode::Depth(){
    return 0;
}

BT::ConditionNode::ConditionNode(std::string name) : LeafNode::LeafNode(name)
{
    type_ = BT::CONDITION_NODE;
}
int BT::ConditionNode::DrawType()
{
    return BT::CONDITION;
}

BT::ActionNode::ActionNode(std::string name) : LeafNode::LeafNode(name)
{
    type_ = BT::ACTION_NODE;
}
int BT::ActionNode::DrawType()
{
    return BT::ACTION;
}