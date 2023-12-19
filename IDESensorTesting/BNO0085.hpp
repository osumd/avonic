#ifndef BNO0085_H
#define BNO0085_H

#include <Adafruit_BNO08x.h>
#include "XTSG04.hpp"

#define BNO08X_INT 9

// but not for I2C or UART
#define BNO08X_RESET -1


struct bno0085
{

    Adafruit_BNO08x  bno08x;

  // Top frequency is about 250Hz but this report is more accurate
    sh2_SensorId_t reportType;
    long reportIntervalUs;

    bno0085() : bno08x(BNO08X_RESET), reportType(SH2_ARVR_STABILIZED_RV), reportInterval(5000)
    {
      
    }

    void setReports(sh2_SensorId_t reportType, long report_interval) {
      Serial.println("Setting desired reports");
      if (! bno08x.enableReport(reportType, report_interval)) {
        Serial.println("Could not enable stabilized remote vector");
      }
    }

    void OnStart()
    {
      if (!bno08x.begin_I2C()) {
        Serial.println("Failed to find BNO08x chip");
        while (1) { delay(10); }
      }
      Serial.println("BNO08x Found!");

     
      setReports(reportType, reportIntervalUs);

      Serial.println("Reading events");
      delay(100);
    }

    void InitateReadings(xtsg04* file)
    {
      file->WriteToFile("_RAW_ACCELEROMETER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_ACCELEROMETER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_LINEAR_ACCELERATION :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_GRAVITY :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_RAW_GYROSCOPE :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_GYROSCOPE_CALIBRATED :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_GYROSCOPE_UNCALIBRATED :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_RAW_MAGNETOMETER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_MAGNETIC_FIELD_CALIBRATED :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_MAGNETIC_FIELD_UNCALIBRATED :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_ROTATION_VECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_GAME_ROTATION_VECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_GEOMAGNETIC_ROTATION_VECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_PRESSURE :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_AMBIENT_LIGHT :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_HUMIDITY :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_PROXIMITY :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_TEMPERATURE :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_RESERVED :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_TAP_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_STEP_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_STEP_COUNTER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_SIGNIFICANT_MOTION :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_STABILITY_CLASSIFIER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_SHAKE_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_FLIP_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_PICKUP_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_STABILITY_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_PERSONAL_ACTIVITY_CLASSIFIER :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_SLEEP_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_TILT_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_CIRCLE_DETECTOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_HEART_RATE_MONITOR :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_ARVR_STABILIZED_RV :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile("_ARVR_STABILIZED_GRV :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile(sensorValue.un.gyro_integratedRv,"bno005report.txt");
      file->WriteToFile("_GYRO_INTEGRATED_RV :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile(sensorValue.un.izro_motionRequest,"bno005report.txt");
      file->WriteToFile("_IZRO_MOTION_REQUEST :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
      file->WriteToFile(sensorValue.un.max_sensorId,"bno005report.txt");
      file->WriteToFile("_MAX_SENSOR_ID :","bno005report.txt");
      file->WriteToFile(",","bno005report.txt");
    }

    void ReportReadings(xtsg04* file)
    {

      if (bno08x.wasReset()) {
        Serial.print("sensor was reset");
        setReports(reportType, reportIntervalUs);
      }
      
      sh2_SensorValue_t sensorValue;
      
      if (bno08x.getSensorEvent(&sensorValue)) {
        // in this demo only one report type will be received depending on FAST_MODE define (above)
        switch (sensorValue.sensorId) {
            case SH2_RAW_ACCELEROMETER :
              Serial.print("_RAW_ACCELEROMETER :");
              Serial.print(sensorValue.un.rawAccelerometer);
              
              file->WriteToFile(sensorValue.un.rawAccelerometer);
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_ACCELEROMETER :
              Serial.print("_ACCELEROMETER :");
              Serial.print(sensorValue.un.accelerometer);
              
              file->WriteToFile(sensorValue.un.accelerometer,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_LINEAR_ACCELERATION :
              Serial.print("_LINEAR_ACCELERATION :");
              Serial.print(sensorValue.un.linearAcceleration);
              
              file->WriteToFile(sensorValue.un.linearAcceleration,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GRAVITY :
              Serial.print("_GRAVITY :");
              Serial.print(sensorValue.un.gravity);
              
              file->WriteToFile(sensorValue.un.gravity,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_RAW_GYROSCOPE :
              
              file->WriteToFile(sensorValue.un.rawGyroscope,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GYROSCOPE_CALIBRATED :
              
              file->WriteToFile(sensorValue.un.gyroscopeCalibrated,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GYROSCOPE_UNCALIBRATED :
              
              file->WriteToFile(sensorValue.un.gyroscopeUncalibrated,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_RAW_MAGNETOMETER :
              
              file->WriteToFile(sensorValue.un.rawMagnetometer,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_MAGNETIC_FIELD_CALIBRATED :
              Serial.print("_MAGNETIC_FIELD_CALIBRATED :");
              Serial.print(sensorValue.un.magnetic_fieldCalibrated);
              
              file->WriteToFile(sensorValue.un.magnetic_fieldCalibrated,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_MAGNETIC_FIELD_UNCALIBRATED :
              
              file->WriteToFile(sensorValue.un.magnetic_fieldUncalibrated,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_ROTATION_VECTOR :
              Serial.print("_ROTATION_VECTOR :");
              Serial.print(sensorValue.un.rotationVector);
              
              file->WriteToFile(sensorValue.un.rotationVector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GAME_ROTATION_VECTOR :
              
              file->WriteToFile(sensorValue.un.game_rotationVector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GEOMAGNETIC_ROTATION_VECTOR :
              Serial.print("_GEOMAGNETIC_ROTATION_VECTOR :");
              Serial.print(sensorValue.un.geomagnetic_rotationVector);
              
              file->WriteToFile(sensorValue.un.geomagnetic_rotationVector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_PRESSURE :
              Serial.print("_PRESSURE :");
              Serial.print(sensorValue.un.pressure);
              
              file->WriteToFile(sensorValue.un.pressure,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_AMBIENT_LIGHT :
              Serial.print("_AMBIENT_LIGHT :");
              Serial.print(sensorValue.un.ambientLight);
              
              file->WriteToFile(sensorValue.un.ambientLight,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_HUMIDITY :
              Serial.print("_HUMIDITY :");
              Serial.print(sensorValue.un.humidity);
              
              file->WriteToFile(sensorValue.un.humidity,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_PROXIMITY :
              Serial.print("_PROXIMITY :");
              Serial.print(sensorValue.un.proximity);
              
              file->WriteToFile(sensorValue.un.proximity,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_TEMPERATURE :
              Serial.print("_TEMPERATURE :");
              Serial.print(sensorValue.un.temperature);
              
              file->WriteToFile(sensorValue.un.temperature,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_RESERVED :
              
              file->WriteToFile(sensorValue.un.reserved,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_TAP_DETECTOR :
              
              file->WriteToFile(sensorValue.un.tapDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_STEP_DETECTOR :
              
              file->WriteToFile(sensorValue.un.stepDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_STEP_COUNTER :
              
              file->WriteToFile(sensorValue.un.stepCounter,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_SIGNIFICANT_MOTION :
              
              file->WriteToFile(sensorValue.un.significantMotion,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_STABILITY_CLASSIFIER :
              
              file->WriteToFile(sensorValue.un.stabilityClassifier,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_SHAKE_DETECTOR :
              
              file->WriteToFile(sensorValue.un.shakeDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_FLIP_DETECTOR :
              
              file->WriteToFile(sensorValue.un.flipDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_PICKUP_DETECTOR :
              
              file->WriteToFile(sensorValue.un.pickupDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_STABILITY_DETECTOR :
              
              file->WriteToFile(sensorValue.un.stabilityDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_PERSONAL_ACTIVITY_CLASSIFIER :
              
              file->WriteToFile(sensorValue.un.personal_activityClassifier,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_SLEEP_DETECTOR :
              
              file->WriteToFile(sensorValue.un.sleepDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_TILT_DETECTOR :
              
              file->WriteToFile(sensorValue.un.tiltDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_POCKET_DETECTOR :
              Serial.print("_POCKET_DETECTOR :");
              
            case SH2_CIRCLE_DETECTOR :
              
              file->WriteToFile(sensorValue.un.circleDetector,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_HEART_RATE_MONITOR :
              
              file->WriteToFile(sensorValue.un.heart_rateMonitor,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_ARVR_STABILIZED_RV :
              
              file->WriteToFile(sensorValue.un.arvr_stabilizedRv,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_ARVR_STABILIZED_GRV :
              
              file->WriteToFile(sensorValue.un.arvr_stabilizedGrv,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");
              break;
            case SH2_GYRO_INTEGRATED_RV :
              file->WriteToFile(sensorValue.un.gyro_integratedRv,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");;
              
              break;
            case SH2_IZRO_MOTION_REQUEST :
              file->WriteToFile(sensorValue.un.izro_motionRequest,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");;
              
              break;
            case SH2_MAX_SENSOR_ID :
              file->WriteToFile(sensorValue.un.max_sensorId,"bno005report.txt");
              file->WriteToFile(",","bno005report.txt");;
              
              break;
            default:
              break;

        }

      }

      file->WriteToFile("hello");
    }

    void OnUpdate()
    {
      if (bno08x.wasReset()) {
        Serial.print("sensor was reset");
        setReports(reportType, reportIntervalUs);
      }
      
      sh2_SensorValue_t sensorValue;
      
      


    }

    ~bno0085()
    {

    }
};

#endif