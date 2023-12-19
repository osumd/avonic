#ifndef ADXL_375
#define ADXL_375

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL375.h>

#define ADXL375_SCL 19
#define ADXL375_SDA 18

struct adxl375
{
  Adafruit_ADXL375 accel = Adafruit_ADXL375(80084231);
  bool DeviceConnected;

  adxl375() : DeviceConnected(false)
  {

  }


  void OnStart()
  {
      if(!accel.begin()) //Optional specific address specification but uneccecary as it appears that is may default to 0x53
      {
        /* There was a problem detecting the ADXL375 ... check your connections */
        DeviceConnected = false;
      }

      DeviceConnected = true;
  }

  void OnUpdate()
  {

      if(DeviceConnected == false)
      {
        return;
      }
      //accelerational data printing
      sensors_event_t event;
      accel.getEvent(&event);

      /* Display the results (acceleration is measured in m/s^2) */
      Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
      Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
      Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
      delay(500);
  }


};


#endif