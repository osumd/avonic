#ifndef FPG_M_H
#define FPG_M_H

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#include "XTSG04.hpp"

#define GPSSerial Serial8
#define GPSECHO false


struct fpgm
{
  SoftwareSerial mySerial;
  Adafruit_GPS GPS;
  uint32_t timer;

  fpgm() : mySerial(35,34), GPS(&mySerial),timer(millis())
  {

  }

  void OnStart()
  {

    Serial.println("Hello world");
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);
    //delay(1000);
    mySerial.println(PMTK_Q_RELEASE);

    
  }

  void OnUpdate()
  {
    //Serial.println("Serial Mode");

    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if ((c) && (GPSECHO))
      Serial.write(c);

    // if a sentence is received, we can check the checksum, parse it...
    Serial.print("GPS record: ");
    Serial.println(GPS.newNMEAreceived());
    if (GPS.newNMEAreceived()) {
      // a tricky thing here is if we print the NMEA sentence, or data
      // we end up not listening and catching other sentences!
      // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
      //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

      if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000) {
      timer = millis(); // reset the timer

      Serial.print("\nTime: ");
      if (GPS.hour < 10) { Serial.print('0'); }
      Serial.print(GPS.hour, DEC); Serial.print(':');
      if (GPS.minute < 10) { Serial.print('0'); }
      Serial.print(GPS.minute, DEC); Serial.print(':');
      if (GPS.seconds < 10) { Serial.print('0'); }
      Serial.print(GPS.seconds, DEC); Serial.print('.');
      if (GPS.milliseconds < 10) {
        Serial.print("00");
      } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
        Serial.print("0");
      }
      Serial.println(GPS.milliseconds);
      Serial.print("Date: ");
      Serial.print(GPS.day, DEC); Serial.print('/');
      Serial.print(GPS.month, DEC); Serial.print("/20");
      Serial.println(GPS.year, DEC);
      Serial.print("Fix: "); Serial.print((int)GPS.fix);
      Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
      if (GPS.fix) {
        Serial.print("Location: ");
        Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
        Serial.print(", ");
        Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);

        Serial.print("Speed (knots): "); Serial.println(GPS.speed);
        Serial.print("Angle: "); Serial.println(GPS.angle);
        Serial.print("Altitude: "); Serial.println(GPS.altitude);
        Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
        Serial.print("Antenna status: "); Serial.println((int)GPS.antenna);
      }
    }
  }

  void InitateReadings(xtsg04* file)
  {
    file->WriteToFile("Location", "gpsSensor.txt");
    file->WriteToFile("Speed (knots)", "gpsSensor.txt");
    file->WriteToFile("angle", "gpsSensor.txt");
    file->WriteToFile("Altitude", "gpsSensor.txt");
    file->WriteToFile("Satellites", "gpsSensor.txt");
    file->WriteToFile("Antenna status", "gpsSensor.txt");
    file->WriteToFile("Latitude (Degrees)", "gpsSensor.txt");
    file->WriteToFile("Longitude (Degrees)", "gpsSensor.txt");
  }
  
  void ReportReadings(xtsg04* file)
  {
    if (GPS.newNMEAreceived()) {
      // Parse NMEA sentences
      if (!GPS.parse(GPS.lastNMEA())) {
        return;
      }

      Serial.print("Date: ");
      Serial.print(GPS.day, DEC); Serial.print('/');
      Serial.print(GPS.month, DEC); Serial.print("/20");
      Serial.println(GPS.year, DEC);
      Serial.print("Fix: "); Serial.print((int)GPS.fix);
      Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
      // Check if the GPS data is valid

      Serial.print("GPS Fix Factor: ");
      Serial.println(GPS.fix);
      if (GPS.fix) {

        Serial.print("Location: ");
        Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
        Serial.print(", ");
        Serial.print(GPS.longitude, 4); 
        Serial.println(GPS.lon);
        Serial.print("Speed (knots): "); 
        Serial.println(GPS.speed);
        Serial.print("Angle: "); 
        Serial.println(GPS.angle);
        Serial.print("Altitude: "); 
        Serial.println(GPS.altitude);
        Serial.print("Satellites: "); 
        Serial.println((int)GPS.satellites);
        Serial.print("Antenna status: "); 
        Serial.println((int)GPS.antenna);
        // Print latitude, longitude, and altitude
        Serial.print("Latitude (Degrees): "); 
        Serial.println(GPS.latitudeDegrees, 4);
        Serial.print("Longitude (Degrees): "); 
        Serial.println(GPS.longitudeDegrees, 4);
        Serial.println("=======================");

        file->WriteToFile("Location: ","gpsSensors.txt");
        file->WriteToFile(GPS.latitude, "gpsSensors.txt");
        file->WriteToFile(", ","gpsSensors.txt"); 
        file->WriteToFile(GPS.lat,"gpsSensors.txt");
        file->WriteToFile(", ","gpsSensors.txt");
        file->WriteToFile(GPS.longitude,"gpsSensors.txt");
        file->WriteToFile(", ","gpsSensors.txt"); 
        file->WriteToFile(GPS.lon, "gpsSensors.txt");
        file->WriteToFile(", ","gpsSensors.txt");
        file->WriteToFile("Speed (knots)", "gpsSensors.txt"); 
        file->WriteToFile(GPS.speed,"gpsSensors.txt");
        file->WriteToFile("Angle: ","gpsSensors.txt"); 
        file->WriteToFile(GPS.angle, "gpsSensors.txt");
        file->WriteToFile("Altitude: ","gpsSensors.txt"); 
        file->WriteToFile(GPS.altitude, "gpsSensors.txt");
        file->WriteToFile("Satellites: ","gpsSensors.txt"); 
        file->WriteToFile((int)GPS.satellites, "gpsSensors.txt");
        file->WriteToFile("Antenna status: ","gpsSensors.txt"); 
        file->WriteToFile((int)GPS.antenna, "gpsSensors.txt");
        file->WriteToFile("Latitude (Degrees)","gpsSensors.txt"); 
        file->WriteToFile(GPS.latitudeDegrees, "gpsSensors.txt");
        file->WriteToFile("Longitude (Degrees)","gpsSensors.txt"); 
        file->WriteToFile(GPS.longitudeDegrees,"gpsSensors.txt");
        file->WriteToFile("=======================", "gpsSensors.txt");

      }
    }
  }

  ~fpgm()
  {

  }
};

#endif