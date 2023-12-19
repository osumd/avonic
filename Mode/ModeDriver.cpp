
#include <iostream>
#include "AvionicsModeStages/avIdleMode.h"


avMode      AttachedModes[3];       // List of currently active modes.
avMode*     currentMode;            // Currently activated mode.

void InitalizeModes()
{
    IdleModeInit(&AttachedModes[0]);        //Establish mode zero as the idle mode.
    
}

void Loop()
{
    //Important to note that using self, alot can increase flexability but can also be removed.

    //Need a section here to listen for analog and telemetric control systems, if external communication is neccecary.
    
    currentMode->Runtime(currentMode);

    if(currentMode->avModeSwitchFlag.aModeSwitchDetected == true)
    {
        ResetModeFlags(currentMode);                                        //Reset if neccecary.
        currentMode = &AttachedModes[currentMode->avModeSwitchFlag.switchTo];  
    }
}

int main()
{
    InitalizeModes();
    currentMode = &AttachedModes[MODE_IDLE_LAUNCH_WAITING];
    Loop();
}