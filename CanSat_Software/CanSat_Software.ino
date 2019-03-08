// INCLUDES
#include <SPI.h>
#include <RH_RF95.h>
#include <RHReliableDatagram.h>


// RADIO CHANNELS
const unsigned short int RH_CHANNEL_GS_ALPHA = 1;   //
const unsigned short int RH_CHANNEL_GS_DELTA = 2;   //
const unsigned short int RH_CHANNEL_MU = 3;         // Available radio-network-channels
const unsigned short int RH_CHANNEL_BETA = 4;       //
const unsigned short int RH_CHANNEL_RHO = 5;        //

const unsigned short int RH_CHANNEL_LOCAL = RH_CHANNEL_BETA; // Set local channel, used by the programme

// PIN DEFINITIONS
const unsigned short int PIN_RH_RST = 10;    //
const unsigned short int PIN_RH_CS = 12;     // Setting: RHDriver pins
const unsigned short int PIN_RH_INT = 6;    //

const float RHDriverFreq = 868.0;   // RHDriver Frequency

// RADIO DECLARATION
RH_RF95 RHDriver(PIN_RH_CS, PIN_RH_INT);
RHReliableDatagram RHNetwork(RHDriver, RH_CHANNEL_LOCAL);





// SETUP FUNCTION
void setup(){
  Serial.begin(115200);
  delay(1000);
  // --------------- Initializing RH_Datagram -------------------- //
  if(!RHNetwork.init()){
    while(1);
  }

  // --------------- Setting RH_Driver frequency -------------------- //

  if(!RHDriver.setFrequency(RHDriverFreq)){
    while(1);
  }

  // --------------- Setting RH_Driver TxPower to 23 (maximum) -------------------- //

  RHDriver.setTxPower(23, false);

  // --------------- Setting #retries for RH_Datagram -------------------- //

  RHNetwork.setRetries(0);

  // --------------- Setting duration timeout for RH_Datagram -------------------- //

  RHNetwork.setTimeout(0);
}



// LOOP FUNCTION
void loop(){
  delay(100);
  String send = "{CAN:" + String(RH_CHANNEL_LOCAL) + ";GT:123;ST:12394;}";
  RHNetwork.sendtoWait((uint8_t*)send.c_str(), send.length(), RH_CHANNEL_GS_ALPHA);
}
