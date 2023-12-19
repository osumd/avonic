#ifndef AV_MODE_SWITCH_FLAG
#define AV_MODE_SWITCH_FLAG

#include "../avModeIdentifier.h"

struct avModeSwitchFlag
{
    bool aModeSwitchDetected;
    bool multipleModeSwitchesDetected;
    avModeIdentifier  switchTo;

    avModeSwitchFlag() :aModeSwitchDetected(false), multipleModeSwitchesDetected(false)
    {
        
    }
};

#endif