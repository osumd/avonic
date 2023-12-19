#ifndef MODE_SWITCH_CONDTIONS_H
#define MODE_SWITCH_CONDTIONS_H 

#include "../avModeIdentifier.h"
#include "avModeSwitchFlag.h"
#include "avModeSwitchType.h"

struct avModeSwitchCondition
{
    avModeIdentifier switchTo;
    //This function passes itself in and must be declared globally.
    void*   self;
    bool(*switchCondition)(void* self);   //This conitions when met calls will indicate a switch is needed.
};



#endif