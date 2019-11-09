/*
    Quectel.C - A small library for the Quectel BG96
    Author: Luca Panjer
*/
#include "Arduino.h"
#include "quectel.h"

#include <SoftwareSerial.h>

SoftwareSerial BG96Serial(RXPIN, TXPIN);

/*
    Starts the communication with the module by confirming that we have a UART connection
    This is done by sending "AT" and waiting for the module to respond with "OK".
*/
bool Quectel::Begin()
{
    BG96Serial.begin(BAUDRATE);
    //TODO: send AT and wait for OK

    Serial.println("BG96 Started!");
    return true;
}

/*
    Reads the given string and parses it into a byte that is more easily readable.
*/
byte Quectel::ParseResponse(String response)
{
    if(response.indexOf("OK") > 0)
        return OK;
    if(response.indexOf("ERROR"))
        return ERROR;
    if(response.indexOf("SEND OK"))
        return SENDOK;
        
    return 0;
}

/*
    Reads the string response from the BG96Serial buffer and returns it.
    CHECKS FOREVER! ONLY USE WHEN YOU ARE SURE THE MODULE HAS RESPONDED!

    TODO: Make this check for about a second instead of forever
*/
String Quectel::GetResponse()
{
    while(!BG96Serial.available());
    return BG96Serial.readString();
}

/*
    Reads the incoming string command and prefixes it with "AT+".
    After that, it sends the command trough the BG96Serial.
    Returns the parsed response when done. 
*/
byte Quectel::SendCommand(String command)
{
    String message;
    if(command == "")
        message = "AT";
    else
        message = "AT+" + command;
        
    BG96Serial.println(message);

    String response = GetResponse();
    return ParseResponse(response);
}

/*
    Sets the APN to the given URL.
    Does this by sending the QICSGP AT command.

    TODO: implement support for apns that need a username/password
*/
bool Quectel::SetApn(String apn)
{
    //Example for 1nce:
    //AT+QICSGP=1,1,”iot.1nce.net”,””,””,1

    byte result = SendCommand("QICSGP=1,1,\"" + apn + "\"");
    if(result == OK)
        return true;

    return false;
}