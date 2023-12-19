
//Example of SD card usage with the SPI protocol.

//   The circuit:
//    analog sensors on analog ins 0, 1, and 2
//    SD card attached to SPI bus as follows:
//  ** MOSI - pin 11
//  ** MISO - pin 12
//  ** CLK - pin 13
//  ** CS - pin 36 (for MKRZero SD: SDCARD_SS_PIN)


#include <SPI.h>
#include <SD.h>

const int XTSD04GChipSelect = 36;

void setup()
{
    Serial.begin(9600);
    if(!Serial)
    {
        //Wait for serial to initialize before trying
        //to start the SD chip.
    }

    Serial.print("Initalize SD card..");
    if(!SD.begin(XTSD04GChipSelect))
    {
        Serial.println("Card failed, or not present");
        
        //Terminate program.
    }

    Serial.println("SD card initialized.");
}


void writingToFile()
{
    const char* dataString = "data";

    //   nameOfFile         Open   FileName     Inout
    File fileonXTSD04G = SD.open("imuData.txt", FILE_WRITE);

    //If the file is not null
    if(fileonXTSD04G)
    {
        fileonXTSD04G.println(dataString);
        fileonXTSD04G.close();

        Serial.println("Successfuly entered data to the SD unit");
    }else{
        Serial.println("Could not open the file present on the SD device");
    }
}


void readingToFile()
{

    const char buffer[255];

    File fileonXTSD04G = SD.open("imuData.txt", FILE_READ);

    if(fileonXYSD04G)
    {
        int readStatus = fileonXYSD04G.read(buffer, 255);

        Serial.println("Found information on device you must know about.");

        Serial.println(buffer);

        
    
    }else{
        Serial.println("Could not find file, or SD card not connected properly.");
    }




}

void loop()
{


}

int main()
{

}