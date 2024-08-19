/*
 *When light is shined on the photoresistor, play screaming sound effect, trigger fog machine and flash lights

For the music shield there are three 'totally fixed' pins, the hardware SPI pins:
 *SPI SCK - connected to Digital #13 (but can be connected to the ISP header with a jumper) - used by both the SD card and VS1053
 *SPI MISO - connected to Digital #12 (but can be connected to the ISP header with a jumper) - used by both the SD card and VS1053
 *SPI MOSI - connected to Digital #11 (but can be connected to the ISP header with a jumper) - used by both the SD card and VS1053
There are a couple other pins that are required for talking to the VS1053 to play MP3s and such
 *MCS - this is the VS1053 chip select pin, connected to Digital #7
 *DCS - this is the VS1053 data select pin, connected to Digital #6
 *CCS - this is the SD Card chip select pin, connected to Digital #4
 *DREQ - this is the VS1053 data request interrupt pin - connected to digital #3
 */
 
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
 
// pin assignments
 int LightSensorPin = 0;     //Attach photoresister SIG to Pin A0
 int LightThresholdPot = A1;  //Sets threshold value for light sensor (0-1023 with 5v pot)
 int FogPin = 30;            //Pin to fog machine relay attached to digital pin 30
 int LightPin = 32;          //Pin to turn on outlet attach to digital pin 32
 int ShakePin = 34;          //Pin to turn outlet on and off quickly attach to digital pin 34
 int MagLock = 36;           //Pin to turn OFF outlet attach to digital pin 36
 int relayPin38 = 38;        //Pin to relay, constant on for speaker
 int relayPin40 = 40;      //Unused
 int ShakePin2 = 42;         //Pin to turn outlet on and off quickly attach to digital pin 42
 int LightPin2 = 44;      //Unused

 #define manualButton = 46;  //Button for manual trigger

// These are the pins used for the music maker shield
#define SHIELD_RESET  -1     // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
// create shield-example object!
Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

 
// initialize the serial port
// and declare inputs and outputs
 void setup() {
   Serial.begin(9600);
   pinMode(LightSensorPin, INPUT);
   pinMode(LightThresholdPot, INPUT);
   pinMode(FogPin, OUTPUT);
   pinMode(LightPin, OUTPUT);
   pinMode(LightPin2, OUTPUT);
   pinMode(ShakePin, OUTPUT);
   pinMode(ShakePin2, OUTPUT);
   pinMode(MagLock, OUTPUT);
   pinMode(relayPin38, OUTPUT);
   pinMode(relayPin40, OUTPUT);

// test and start music shield, list files and etc   
   Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

// list files
  printDirectory(SD.open("/"), 0);
  
// Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(5,5);

// If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
// audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

 }
 


 void loop() {
   digitalWrite(FogPin,HIGH);                            //Set fog machine to off
   digitalWrite(LightPin,HIGH);
   digitalWrite(LightPin2,HIGH);
   digitalWrite(ShakePin,HIGH);
   digitalWrite(ShakePin2,HIGH);
   digitalWrite(MagLock,LOW);
   digitalWrite(relayPin38,LOW);
   digitalWrite(relayPin40,LOW);
   int LightSensorThreshold = analogRead(LightThresholdPot); //Value set by potentiometer to trigger sequence 
   int LightSensorValue = analogRead(LightSensorPin);    //Create variable to hold light sensor value
   Serial.println(LightSensorValue);                     //Print light sensor value on serial monitor
   delay(100);                                           //slight delay to make for easier reading, can be adjusted

   if (LightSensorValue < LightSensorThreshold)          //If light sensor value goes above 550, should be adjusted based on room lighting, was 800 in 2024
   {
    Serial.println("Light Detected");                    //Print "Light Detected" in serial monitor
    digitalWrite(FogPin, LOW);                           //Turn on fog machine
    digitalWrite(LightPin, LOW);
    digitalWrite(LightPin2, LOW);
    delay(5000);                                        //Delay to allow fog to fill coffin
    
    Serial.println(F("Playing track 001"));             //Start playing track in background
    musicPlayer.startPlayingFile("track001.mp3");
    delay(8000);    
    musicPlayer.startPlayingFile("track002.mp3");
    digitalWrite(FogPin, HIGH);
    
    digitalWrite(ShakePin, LOW);                        //Shaking commences
    digitalWrite(ShakePin2, LOW);
    delay(250);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(150);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(350);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(350);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(450);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(250);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(150);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(150);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(350);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(150);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(450);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(550);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(250);  
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(250);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(450);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(350);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(250);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(150);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(150);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(250);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(350);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(450);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(550);
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);
    delay(650);
    digitalWrite(ShakePin, LOW);                    
    digitalWrite(ShakePin2, LOW);
    delay(750);                       
    digitalWrite(ShakePin, HIGH);
    digitalWrite(ShakePin2, HIGH);                     //Shaking ends
    
    digitalWrite(FogPin, HIGH);                       //Turn off fog machine
    


    digitalWrite(MagLock, HIGH);                      //Open mag lock to final door
    delay(30000);
    digitalWrite(MagLock, LOW);                       //Relock final door
    digitalWrite(LightPin, HIGH);                     //Turn off light and reset
    digitalWrite(LightPin2, HIGH);
    }
 }




/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

