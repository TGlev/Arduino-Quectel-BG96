/*
    Quectel.h - A small library that allows to send TCP data using the Quectel BG96 module.
*/
#ifndef Quectel_h
#define Quectel_h
/*
    Quectel has a dependency of SoftwareSerial. 
    SoftwareSerial is used to communicate with the Quectel module.
*/
#include "Arduino.h"
#include <SoftwareSerial.h>

//Used by SoftwareSerial
//Default values are the pins used by the Dragino Arduino Shield
#define RXPIN 10
#define TXPIN 11

//Used for reading the status byte
#define NOTCONNECTED 2
#define CONNECTED 1

//Used for reading the response byte from ReadResponse()
#define OK 1
#define ERROR 2
#define SENDOK 3

//Used to set which context and which connectid you want to be used.
#define CONTEXT 1
#define CONNECTID 0

#define BAUDRATE 9600

class Quectel
{
    public:
        //VARIABLES
        byte status;
        
        //FUNCTIONS
        bool Begin();
        void SetDebug(bool debug);
        bool SetApn(String apn);
        
    private:
        //VARIABLES
        bool _isDebug;

        //FUNCTIONS
        byte SendCommand(String command);
        String GetResponse();
        byte ParseResponse(String response);
        void PrintDebug(String message);
        byte ReadResponse();
};

#endif