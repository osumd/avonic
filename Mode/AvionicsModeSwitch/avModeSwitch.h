#ifndef AVIONICS_MODE_SWITCH_H
#define AVIONICS_MODE_SWITCH_H


//Include simple pool for dynamic switch conditions if neccecary.
#include "avModeSwitchConditions.h"

const int MAX_SWITCHES = 3;


//Update to design change
struct avModeSwitch
{
    avModeSwitchCondition    modeSwitchConditions[MAX_SWITCHES];      //A list of conditions which can switch modes from within the mode itself.  
    int                      n_switchCondtions;                       //Number of switch condtions present which need to be checked at runtime.    
    avModeSwitchFlag         modeSwitchFlag;                          //A flag set which acts as a communication channel between the main program and the mode.

    avModeSwitch()
    {   
        n_switchCondtions=0;
    }

    void insertCondition(void* self, bool(*switchCondition)(void* self), avModeIdentifier switchTo)
    {
        
        modeSwitchConditions[n_switchCondtions].self;                               //,,, Sets
        modeSwitchConditions[n_switchCondtions].switchCondition = switchCondition;
        modeSwitchConditions[n_switchCondtions].switchTo;

        n_switchCondtions++;                                                        //Increment amount of switch conditions present.
    }

};




#endif