/*
 * File:   newmain.c
 * Author: kater
 *
 * Created on 20. listopadu 2019, 15:25
 */


#include "PICF18LF46K22_ConfigSFR.h"
#include "MCP23017_FunctionLib.h"

//defined init fce
void InitDevice(){
    OSCCON=0b01111100; //osc setting, 16 MHz, internal by FOSCH
    //LEDs on port for show result data
    ANSELD=0;
    TRISD=0;
    
}
//defined clear fce
void ClearDevice(){
    PORTD=0;
}
//defined test fce
void TestDevice(){
    return;
}

void main(void) {
    InitDevice();
    ClearDevice();
    TestDevice();
    Init_MCP23017(0x00);
    Set_DirectionOfPort(IODIRA, 0xFF);
    Set_DirectionOfPort(IODIRB, 0x00);
    Send_DataToPort(GPIOB, 0xFF);
    PORTD=0xAA;
    while(1);
}
