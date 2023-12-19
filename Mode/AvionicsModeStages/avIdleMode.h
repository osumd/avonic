#ifndef IDLE_MODE_H
#define IDLE_MODE_H

#include "../avMode.h"


bool CheckValveTestStatus(void* self)
{
    avMode* mode = (avMode*)self;

    if(mode->flags & 0b00000001)
    {
        return true;
    }

    return false;
}

void IdleModeInit(avMode* mode)
{

    mode->modeIdentifier =      MODE_IDLE_LAUNCH_WAITING;

    //Manually switch based on external flag.
    avModeSwitchCondition                 manualSwitchCondition;
    manualSwitchCondition.self            = mode;
    manualSwitchCondition.switchCondition = CheckValveTestStatus;
    manualSwitchCondition.switchTo        = MODE_VALVE_TESTING;

    //All in one to switch.
    mode->modeSwitches.insertCondition(mode, CheckValveTestStatus, MODE_VALVE_TESTING);
    mode->Runtime = IdleModeRuntime;
    mode->Startup = IdleModeStartup;
    
}

void IdleModeStartup(avMode* mode)
{

    // Set up and test all on board sensors.
    // Test telemetry messaging.

}

void IdleModeRuntime(avMode* mode)
{

    if(mode->avModeSwitchFlag.aModeSwitchDetected == false) //Basic way of telling whether to keep on with the stage method.
    {
        for(int i = 0; i < mode->modeSwitches.n_switchCondtions; i++)
        {
            bool    ModeSwitchEncountered = mode->modeSwitches.modeSwitchConditions[i].switchCondition(mode);
            if(ModeSwitchEncountered == true)
            {
                mode->avModeSwitchFlag.aModeSwitchDetected = true;
                mode->avModeSwitchFlag.switchTo = mode->modeSwitches.modeSwitchConditions[i].switchTo;
                i = mode->modeSwitches.n_switchCondtions;
            }
        }
    }

}











#endif