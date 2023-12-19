#include <Arduino.h>
// This demo explores two reports (SH2_ARVR_STABILIZED_RV and SH2_GYRO_INTEGRATED_RV) both can be used to give 
// quartenion and euler (yaw, pitch roll) angles.  Toggle the FAST_MODE define to see other report.  
// Note sensorValue.status gives calibration accuracy (which improves over time)
#include <Adafruit_BNO08x.h>

// For SPI mode, we need a CS pin
#define BNO08X_INT 9

// but not for I2C or UART
#define BNO08X_RESET -1



Adafruit_BNO08x  bno08x(BNO08X_RESET);



void setReports(sh2_SensorId_t reportType, long report_interval) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(reportType, report_interval)) {
    Serial.println("Could not enable stabilized remote vector");
  }
}

void setup(void) {

  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit BNO08x test!");

  // Try to initialize!
    if (!bno08x.begin_I2C()) {
      Serial.println("Failed to find BNO08x chip");
      while (1) { delay(10); }
    }
    Serial.println("BNO08x Found!");

    // Top frequency is about 250Hz but this report is more accurate
    sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
    long reportIntervalUs = 5000;
    setReports(reportType, reportIntervalUs);

    Serial.println("Reading events");
    delay(100);
}




void loop() {

  if (bno08x.wasReset()) {
    Serial.print("sensor was reset");
    setReports(reportType, reportIntervalUs);
  }
  

  sh2_SensorValue_t sensorValue;

  if (bno08x.getSensorEvent(&sensorValue)) {
    // in this demo only one report type will be received depending on FAST_MODE define (above)
    switch (sensorValue.sensorId) {
      case SH2_ARVR_STABILIZED_RV:
        
      case SH2_GYRO_INTEGRATED_RV:
        // faster (more noise?)
        break;
    }

  }

}
