#define SHIFTPWM_USE_TIMER2
const int ShiftPWM_latchPin=8;

const bool ShiftPWM_invertOutputs = false;

const bool ShiftPWM_balanceLoad = true;

#include <ShiftPWM.h> 

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 4;
unsigned int numOutputs = numRegisters*8;
unsigned int numRGBLeds = numRegisters*8/3;
unsigned int fadingMode = 0; //start with all LED's off.


char packetBuffer[34];

void setup(){
  while(!Serial){
    delay(100); 
  }
  Serial.begin(9600);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  pinMode(10, OUTPUT);
}

void loop() {
  
if (Serial.available() > 0) 
{
 Serial.readBytes(packetBuffer,34);// 6 is the packetsize
 
 if( packetBuffer[0]=='<' && packetBuffer[34-1]=='>')
 {
 unsigned char val [34-2];
 memcpy(val,packetBuffer+1,34-2);
///////////Now we have a clean input buffer of 4 bytes to use.
 ShiftPWM.SetRGB(0,val[0],val[1],val[2]);
 ShiftPWM.SetRGB(1,val[3],val[4],val[5]);
 ShiftPWM.SetRGB(2,val[6],val[7],val[8]);
 ShiftPWM.SetRGB(3,val[9],val[10],val[11]);
 ShiftPWM.SetRGB(4,val[12],val[13],val[14]);
 ShiftPWM.SetRGB(5,val[15],val[16],val[17]);
 
 ShiftPWM.SetRGB(6,val[18],val[19],val[20]);
 ShiftPWM.SetRGB(7,val[21],val[22],val[23]);
 ShiftPWM.SetRGB(8,val[24],val[25],val[26]);
 ShiftPWM.SetRGB(9,val[27],val[28],val[29]);
  ShiftPWM.SetOne(30,val[30]);
  ShiftPWM.SetOne(31,val[31]);
 //ShiftPWM.SetRGB(10,val[30],val[31],0);
 }
 }
           }

