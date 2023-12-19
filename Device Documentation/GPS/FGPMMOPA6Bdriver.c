#include <Adafruit_GPS.h>

// Connect the GPS Power pin to 3.3V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 2
// Connect the GPS RX (receive) pin to Digital 1

// what's the name of the hardware serial port?
#define GPSSerial Serial1
// Initialize the GPS object
Adafruit_GPS GPS(&GPSSerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

uint32_t timer = millis();

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic parsing test!");
  GPS.begin(9600);
  

  //turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set the update rate of the GPS module (in milliseconds)
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);  // 1 Hz update rate
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);


}

void loop() {
  // Read data from the GPS module
  char c = GPS.read();
  
  // If there's valid data, parse and display it
  if (GPS.newNMEAreceived()) {
    // Parse NMEA sentences
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }
    
    // Check if the GPS data is valid
    if (GPS.fix) {
      // Print latitude, longitude, and altitude
      Serial.print("Latitude: "); 
      Serial.println(GPS.latitudeDegrees, 4);
      Serial.print("Longitude: "); 
      Serial.println(GPS.longitudeDegrees, 4);
      Serial.print("Altitude (meters): "); 
      Serial.println(GPS.altitude);
      Serial.println("=======================");
    }
  }
}
