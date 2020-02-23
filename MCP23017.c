/*
 * File:   newmain.c
 * Author: kater
 *
 * Created on 20. listopadu 2019, 15:25
 */


#include "PICF18LF46K22_ConfigSFR.h"
#include "MCP23017_FunctionLib.h"

#define INTB PORTBbits.RB4 
#define INTA PORTBbits.RB5

//defined init fce
void InitDevice(){
    OSCCON=0b01111100; //osc setting, 16 MHz, internal by FOSCH
    //LEDs on port for show result data
    ANSELD=0;
    TRISD=0;
    
    //Input for INTA and INTB
    ANSELBbits.ANSB4=0;
    ANSELBbits.ANSB5=0;
    TRISBbits.RB4=1;
    TRISBbits.RB5=1;
}
//defined clear fce
void ClearDevice(){
    PORTD=0;
}
//defined test fce
void TestDevice(){
    LATD=0xFF;
    delay_ms(1000);
    LATD=0x00;
    return;
}

void main(void) {
    InitDevice();
    ClearDevice();
    TestDevice();
    
    Init_MCP23017();
    
    Set_DirectionOfPort(IODIRA, 0xF0);
    Set_PullUp(PORT_A_MASK, 0xF0); //pull-up port A
    Set_PortPol(PORT_A_MASK, 0xF0);
    
    Set_DirectionOfPort(IODIRB, 0x00);
    
    Set_IOC(PORT_A_MASK,0xF0,true,0x0F);
    Get_IOC_Cap(PORT_A_MASK); //clear interrupt
    
    /*Set_IOC(PORT_B_MASK,0x0F,true,0xF0);
    Get_IOC_Cap(PORT_B_MASK); //clear intterrupt*/
    
    Send_DataToPort(GPIOA, 0x0F); //!!! clear OLATA! 
    Send_DataToPort(GPIOB, 0xAA);
    
    LATD=Read_DataFromPort(GPIOA);
    delay_ms(1000);
    LATD=0x00;
    
    while(1){
        delay_ms(100);
        if( INTB | INTA ){
            //LATD=Get_IOC_Flag(PORT_A_MASK);
            //delay_ms(500);
            //LATD=Get_IOC_Cap(PORT_A_MASK);
            //delay_ms(500);
            LATD=Read_DataFromPort(GPIOA);
        }else LATD=0x00;
    }
}
