// ---------------------------------------------------------------------
// THIS FILE IS AUTO-GENERATED BY BEHAVIAC DESIGNER, SO PLEASE DON'T MODIFY IT BY YOURSELF!
// ---------------------------------------------------------------------

#ifndef _BEHAVIAC_CUSTOMIZED_TYPES_H_
#define _BEHAVIAC_CUSTOMIZED_TYPES_H_

#include "behaviac/agent/agent.h"

// -------------------
// Customized enums
// -------------------

enum TaskIndividual
{
	NonTask,
	March_gps,
	March_laser,
	Search,
	Remote_Control,
	Assemble,
	Stop,
	Pause,
	Resume,
};

DECLARE_BEHAVIAC_ENUM_EX(TaskIndividual, TaskIndividual);
BEHAVIAC_DECLARE_TYPE_VECTOR_HANDLER(TaskIndividual);


enum ForeFuncState
{
	Running,
	Success,
	Failure,
	Idle,
};

DECLARE_BEHAVIAC_ENUM_EX(ForeFuncState, ForeFuncState);
BEHAVIAC_DECLARE_TYPE_VECTOR_HANDLER(ForeFuncState);


#endif // _BEHAVIAC_CUSTOMIZED_TYPES_H_
