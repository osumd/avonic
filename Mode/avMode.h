#ifndef AVIONICS_MODE_EXAMPLE_H
#define AVIONICS_MODE_EXAMPLE_H


#include "AvionicsModeSwitch/avModeSwitch.h"

typedef struct avMode
{
    avModeIdentifier         modeIdentifier;                                            //A descriptor which uniquely identifies this mode.
    avModeSwitch             modeSwitches;                                              //A behavioural switching descriptor.
    avModeSwitchType         modeSwitchType;                                            //Mainly going to be [Manual vs Automatic] switching behvaior.
    avModeSwitchFlag         avModeSwitchFlag;                                          //Used to tell the switch controller to change switching.
    char                     flags;                                                     //Used to set external flags, meaning of which programmed into mode.


    void                    (*Runtime)(avMode* mode);
    void                    (*Startup)(avMode* mode);
    void                    (*ExternalSwitch)(avMode* mode, avModeIdentifier switchTo);   //Set externally to manually switch to stage.

};


void    ResetModeFlags(avMode* mode)                                                    //Will reset the flags section of the modes just in case.
{

    mode->avModeSwitchFlag.aModeSwitchDetected = false;                                 
    mode->avModeSwitchFlag.multipleModeSwitchesDetected = false;                       //


}


#endif