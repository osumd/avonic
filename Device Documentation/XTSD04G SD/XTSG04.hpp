#ifndef XTSG04_H
#define XTSG04_H

#include <SD.h>

const int XTSD04GChipSelect = 36;

struct xtsg04
{

  bool DeviceConnected;
  File flashFile;

  void OnStart()
  {
      Serial.print("Initalize SD card..");
      if(!SD.begin(XTSD04GChipSelect))
      {
          Serial.println("Card failed, or not present");
          DeviceConnected = false;
          
          //Terminate program.
      }

      DeviceConnected = true;

      Serial.println("SD card initialized.");
  }

  void OpenFileToWrite()
  {
    flashFile = SD.open("testFire.txt", FILE_WRITE);
    if(flashFile)
    {
    }else
    {

    }
  }

  void OnUpdate(dataString)
  {
    if(flashFile)
    {
      fileonXTSD04G.println(dataString);
    }else
    {

    }
  }


};

#endif