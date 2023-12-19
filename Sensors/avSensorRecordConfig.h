#ifndef AV_SENSOR_RECORD_CONFIG_H
#define AV_SENSOR_RECORD_CONFIG_H


typedef struct
{    
    int   sensorIdentifier;
    
    // Tranciever object
    void (*WriteToFile)();
    const char* filePath;
    void (*Trancieve)();

} avSensorDataConfig;

#endif