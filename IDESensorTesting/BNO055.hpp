#ifndef BNO055_H
#define BNO055_H

#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "XTSG04.hpp"

void printEvent(sensors_event_t* event);

void WriteEvents(sensors_event_t* event, xtsg04* file);

struct bno055
{
  Adafruit_BNO055 bno = Adafruit_BNO055(84055, 0x28, &Wire);
  bool DeviceConnected;
  bno055() : DeviceConnected(false)
  {

  }

  void OnStart()
  {
      /* Initialise the sensor */
      if(!bno.begin())
      {
          /* There was a problem detecting the BNO055 ... check your connections */
          //Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
          //while(1);
          DeviceConnected = false;
          return;
      }
      DeviceConnected = true;

      delay(1000);
  }

  void ReportReadings(xtsg04* file)
  {
      if(DeviceConnected == false)
      {
        return;
      }
    /* Get a new sensor event */
    //could add VECTOR_ACCELEROMETER, VECTOR_MAGNETOMETER,VECTOR_GRAVITY...
      sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
      bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
      bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
      bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
      bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
      bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
      bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
      // bno.getQuat();
      // bno.getEvent(, Adafruit_BNO055::VECTOR)
    /* Display the floating point data */
      printEvent(&orientationData);
      printEvent(&angVelocityData);
      printEvent(&linearAccelData);
      printEvent(&magnetometerData);
      printEvent(&accelerometerData);
      printEvent(&gravityData);

      WriteEvents(&orientationData,file);
      WriteEvents(&angVelocityData,file);
      WriteEvents(&linearAccelData,file);
      WriteEvents(&magnetometerData,file);
      WriteEvents(&accelerometerData,file);
      WriteEvents(&gravityData,file);

      int8_t boardTemp = bno.getTemp();
      Serial.println();
      Serial.print(F("temperature: "));
      Serial.println(boardTemp);

      imu::Quaternion quat = bno.getQuat();
      /* Display the quat data */
      Serial.print("qW: ");
      Serial.print(quat.w(), 4);
      Serial.print(" qX: ");
      Serial.print(quat.y(), 4);
      Serial.print(" qY: ");
      Serial.print(quat.x(), 4);
      Serial.print(" qZ: ");
      Serial.print(quat.z(), 4);
      Serial.println("");
      

      uint8_t system, gyro, accel, mag = 0;
      bno.getCalibration(&system, &gyro, &accel, &mag);
      Serial.println();
      Serial.print("Calibration: Sys=");
      Serial.print(system);
      Serial.print(" Gyro=");
      Serial.print(gyro);
      Serial.print(" Accel=");
      Serial.print(accel);
      Serial.print(" Mag=");
      Serial.println(mag);

      Serial.println("--");
      delay(100);
  }

  void OnUpdate()
  {
      if(DeviceConnected == false)
      {
        return;
      }
    /* Get a new sensor event */
    //could add VECTOR_ACCELEROMETER, VECTOR_MAGNETOMETER,VECTOR_GRAVITY...
      sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
      bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
      bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
      bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
      bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
      bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
      bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
      // bno.getQuat();
      // bno.getEvent(, Adafruit_BNO055::VECTOR)
    /* Display the floating point data */
      printEvent(&orientationData);
      printEvent(&angVelocityData);
      printEvent(&linearAccelData);
      printEvent(&magnetometerData);
      printEvent(&accelerometerData);
      printEvent(&gravityData);

      int8_t boardTemp = bno.getTemp();
      Serial.println();
      Serial.print(F("temperature: "));
      Serial.println(boardTemp);

      imu::Quaternion quat = bno.getQuat();
      /* Display the quat data */
      Serial.print("qW: ");
      Serial.print(quat.w(), 4);
      Serial.print(" qX: ");
      Serial.print(quat.y(), 4);
      Serial.print(" qY: ");
      Serial.print(quat.x(), 4);
      Serial.print(" qZ: ");
      Serial.print(quat.z(), 4);
      Serial.println("");
      

      uint8_t system, gyro, accel, mag = 0;
      bno.getCalibration(&system, &gyro, &accel, &mag);
      Serial.println();
      Serial.print("Calibration: Sys=");
      Serial.print(system);
      Serial.print(" Gyro=");
      Serial.print(gyro);
      Serial.print(" Accel=");
      Serial.print(accel);
      Serial.print(" Mag=");
      Serial.println(mag);

      Serial.println("--");
      delay(100);
  }

};

void WriteEvents(sensors_event_t* event, xtsg04* file)
{
double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
    if (event->type == SENSOR_TYPE_ACCELEROMETER) {
      file->WriteToFile("Accl:","bn055readings.txt");
      x = event->acceleration.x;
      y = event->acceleration.y;
      z = event->acceleration.z;
    }
    else if (event->type == SENSOR_TYPE_ORIENTATION) {
      file->WriteToFile("Orient:","bn055readings.txt");
      x = event->orientation.x;
      y = event->orientation.y;
      z = event->orientation.z;
    }
    else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
      file->WriteToFile("Mag:","bn055readings.txt");
      x = event->magnetic.x;
      y = event->magnetic.y;
      z = event->magnetic.z;
    }
    else if (event->type == SENSOR_TYPE_GYROSCOPE) {
      file->WriteToFile("Gyro:","bn055readings.txt");
      x = event->gyro.x;
      y = event->gyro.y;
      z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_ROTATION_VECTOR) {
      file->WriteToFile("Rot:","bn055readings.txt");
      x = event->gyro.x;
      y = event->gyro.y;
      z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_LINEAR_ACCELERATION) {
      file->WriteToFile("Linear:","bn055readings.txt");
      x = event->acceleration.x;
      y = event->acceleration.y;
      z = event->acceleration.z;
    }
    else if (event->type == SENSOR_TYPE_GRAVITY) {
      file->WriteToFile("Gravity:","bn055readings.txt");
      x = event->acceleration.x;
      y = event->acceleration.y;
      z = event->acceleration.z;
    }
    else {
      file->WriteToFile("Unk:","bn055readings.txt");
    }

    file->WriteToFile("	x= ","bn055readings.txt");
    file->WriteToFile(x,"bn055readings.txt");
    file->WriteToFile(" |	y= ","bn055readings.txt");
    file->WriteToFile(y,"bn055readings.txt");
    file->WriteToFile(" |	z= ","bn055readings.txt");
    file->WriteToFile(z,"bn055readings.txt");
    file->WriteToFile("\n", "bn055readings.txt");
}

void printEvent(sensors_event_t* event) {
   
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    Serial.print("Accl:");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  }
  else if (event->type == SENSOR_TYPE_ORIENTATION) {
    Serial.print("Orient:");
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  }
  else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
    Serial.print("Mag:");
    x = event->magnetic.x;
    y = event->magnetic.y;
    z = event->magnetic.z;
  }
  else if (event->type == SENSOR_TYPE_GYROSCOPE) {
    Serial.print("Gyro:");
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  }
  else if (event->type == SENSOR_TYPE_ROTATION_VECTOR) {
    Serial.print("Rot:");
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  }
  else if (event->type == SENSOR_TYPE_LINEAR_ACCELERATION) {
    Serial.print("Linear:");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  }
  else if (event->type == SENSOR_TYPE_GRAVITY) {
    Serial.print("Gravity:");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  }
  else {
    Serial.print("Unk:");
  }

  Serial.print("\tx= ");
  Serial.print(x);
  Serial.print(" |\ty= ");
  Serial.print(y);
  Serial.print(" |\tz= ");
  Serial.println(z);
}

#endif