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

  void OpenFileToWrite(const char* filePath)
  {
    flashFile = SD.open(filePath, FILE_WRITE);
    if(flashFile)
    {
      
    }else
    {
      Serial.println("File not found.");
    }
  }

  void OpenFileToRead(const char* filePath)
  {
    flashFile = SD.open(filePath);
    if(flashFile)
    {
      
    }else
    {
      Serial.println("File not found.");
    }
  }

  void WriteToFile(const char* message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }

  void WriteToFile(double message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }

  void WriteToFile(float message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }

  void WriteToFile(long unsigned int message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }

  void WriteToFile(char message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }

  void WriteToFile(int message, const char* filePath)
  {
      OpenFileToWrite(filePath);
      flashFile.print(message);
      flashFile.close();
  }


  void ReadFile(const char* filePath)
  {
    
    OpenFileToRead(filePath);

    if (flashFile) {
      while (flashFile.available()) {
        Serial.write(flashFile.read());
      }
      flashFile.close();
    }
    else {
      Serial.println("error opening datalog.txt");
    }

  }

  void OnUpdate()
  {

  }


};

#endif