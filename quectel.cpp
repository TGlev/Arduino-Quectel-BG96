/*
    Quectel.C - A small library for the Quectel BG96
    Author: Luca Panjer
*/
#include "Arduino.h"
#include "quectel.h"

#include <SoftwareSerial.h>

SoftwareSerial BG96Serial(RXPIN, TXPIN);

bool Quectel::Begin()
{
    BG96Serial.begin(BAUDRATE);
    Serial.println("BG96 Started!");
    return true;
}

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

String Quectel::GetResponse()
{
    //TODO: Make this check for about a second instead of forever
    while(!BG96Serial.available());

    return BG96Serial.readString();
}

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

bool Quectel::SetApn(String apn)
{
    //Example for 1nce:
    //AT+QICSGP=1,1,”iot.1nce.net”,””,””,1

    byte result = SendCommand("QICSGP=1,1,\"" + apn + "\"");
    if(result == OK)
        return true;

    return false;
}