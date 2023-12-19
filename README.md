# Table of Contents
- [Environment](#Envrionment)
- [Debugging](#Debugging)
- [Mode/Sensors](#Mode/Sensors)
# Environment
Install the following extensions for dependent source code.
## Arduino IDE Extensions

| **Library Name**   | **Sensor**   |
| -------------- | -------------- |
| Adafruit ADXL375  | High G Accelerometer     |
| Adafruit BNO055   | Intertial Measurement Reader     |
| Adafruit GPS Library   |  GPS     |
| Adafruit MCP 23017   | Multiplexer     |
________________________________________
## Previous testing environment download.
Located in /IDESensorTesting, can be copy and pasted into Arduino IDE Sketch path, to use what was previously used for testing.
The structs for these sensors can be restructed for use in the final control system.

# Debugging

## GPS Solutions
Recommended to isolate the connection between teensy and GPS, try all sets of pins.
After installing the Adafruit GPS Library, try to hardware and software example tests with each of the sets sets of pins.

## Thermocouple Solutions
Test in isolation, use ocilloscope to measure the drdy wavelet.

# Mode/Sensors
Coming Soon
To create a mode, you can create a new file etc. TelemetryTest.h

```C++

bool ExampleInternalSwitchCondition()
{
    return false;
}

void TelemetryModeInit(avMode* mode)
{

    mode->modeIdentifier =      MODE_ETC_XXX; //Enum or integer identifier defined in avModeIdentifier.h 

    //Manually switch based on external flag.
    avModeSwitchCondition                 manualSwitchCondition;
    manualSwitchCondition.self            = mode;
    manualSwitchCondition.switchCondition = ExampleInternalSwitchCondition;
    manualSwitchCondition.switchTo        = MODE_ETC_XXX;

    //All in one to switch.
    mode->modeSwitches.insertCondition(mode, CheckValveTestStatus, MODE_VALVE_TESTING);
    mode->Runtime = TelemetryModeRuntime;
    mode->Startup = TelemetryModeStartup;
    
}

void TelemetryModeStartup(avMode* mode)
{

    // Set up and test all on board sensors.
    // Test telemetry messaging.

}

void CheckSwitchConditions(avMode* mode)
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

void IdleModeRuntime(avMode* mode)
{
    CheckSwitchConditions(mode);
    //check sensors

}


```