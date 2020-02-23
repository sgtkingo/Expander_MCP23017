/*
 * File:   Keyboard 4X4 via MCP23017 expander
 * Author: Konecny Jiri
 *
*/

#include "PICF18LF46K22_ConfigSFR.h"
#include "MCP23017_FunctionLib.h"

#define INTB PORTBbits.RB4 
#define INTA PORTBbits.RB5

#define IN_MASK 0xF0
#define OUT_MASK 0x0F

#define ALL_OFF 0x0F

#define COL_A 0x01
#define COL_B 0x02
#define COL_C 0x04
#define COL_D 0x08

#define ROW_A 0x01
#define ROW_B 0x02
#define ROW_C 0x04
#define ROW_D 0x08

void Test_Keyboard(unsigned char out){
    out =  ~out; 
    NOP();
    Send_DataToPort(GPIOA, out & OUT_MASK); 
}

unsigned char Resolve_Keyboard(unsigned char in, unsigned char out){
   if( in == 0 || out == 0) return 0;
   unsigned char result=0;
   if( out == COL_A){
       if( in == ROW_A){
           result=16;
       }
       if( in == ROW_B){
           result=15;
       }
       if( in == ROW_C){
           result=14;
       }
       if( in == ROW_D){
           result=13;
       }       
   }
   if( out == COL_B){
       if( in == ROW_A){
           result=12;
       }
       if( in == ROW_B){
           result=11;
       }
       if( in == ROW_C){
           result=10;
       }
       if( in == ROW_D){
           result=9;
       }       
   }
   if( out == COL_C){
       if( in == ROW_A){
           result=8;
       }
       if( in == ROW_B){
           result=7;
       }
       if( in == ROW_C){
           result=6;
       }
       if( in == ROW_D){
           result=5;
       }       
   }
   if( out == COL_D){
       if( in == ROW_A){
           result=4;
       }
       if( in == ROW_B){
           result=3;
       }
       if( in == ROW_C){
           result=2;
       }
       if( in == ROW_D){
           result=1;
       }       
   }   
   return result;
}

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
    
    unsigned char IN_DATA,OUT_DATA,RESULT;
    
    IN_DATA=RESULT=0;
    OUT_DATA=COL_A;
    
    Set_DirectionOfPort(IODIRA, 0xF0); //1-4 ROWN (IN), 5-8 COLS (OUT)
    Set_PullUp(PORT_A_MASK, 0xF0); //pull-up port A
    Set_PortPol(PORT_A_MASK, 0xF0); //Swap polarization of port A (0 -> 1)
    
    Set_IOC(PORT_A_MASK,0xF0,true,0x0F); //pin 0-3 are IOC, compare to 0 (0 trigger int)
    Get_IOC_Cap(PORT_A_MASK); //clear interrupt
    
    Send_DataToPort(GPIOA, ALL_OFF); 
    
    while(1){
        Test_Keyboard(OUT_DATA);
        delay_ms(100);
        while( INTA ){
            IN_DATA=(Read_DataFromPort(GPIOA) & IN_MASK);
            IN_DATA >>=4;
            if(IN_DATA == 0)break;
            
            LATD=RESULT=Resolve_Keyboard(IN_DATA,OUT_DATA);
            delay_ms(100);
        }
        OUT_DATA*=2;
        if( OUT_DATA > COL_D){
            OUT_DATA=COL_A;
        }
        LATD=IN_DATA=0x00;
    }
}
