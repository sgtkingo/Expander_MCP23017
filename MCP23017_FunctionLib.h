/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * Author: Jiri Konecny 
 * Comments: EEPROM 22LC64 function header for PIC
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCP23017_FUNCTION
#define	MCP23017_FUNCTION

#include "MCP23017_Config.h"

void Send_ConfigToRegister(unsigned char reg, unsigned char cmd);


void ConfigDeviceFast(){
    /*Send_ConfigToRegister(IOCON, 0b00101010); //Config IOCON, no seq BANK=0
    Send_ConfigToRegister(GPPU, 0x00); //Config GPPU, pullup
    Send_ConfigToRegister(INTF, 0x00); //Config INTF, interrrupt
    Send_ConfigToRegister(INTCAP, 0x00); //Config INTCAP, interrrupt pre value
    Send_ConfigToRegister(GPIO, 0x00); //Config GPIO, general purpose register
    Send_ConfigToRegister(OLAT, 0x00); //Config OLAT, output latch register
    
    Send_ConfigToRegister(IOCON, 0b00001010); //Config IOCON, seq BANK=1*/
    
    DEVICE_ADRESS&=WBIT;
    
    I2C_STR();
    WriteI2C(DEVICE_ADRESS);
    WriteI2C(0xFF); //IODIRA
    WriteI2C(0x00); //IODIRB
    WriteI2C(0x00); //IPOLA
    WriteI2C(0x00); //IPOLB
    WriteI2C(0x00); //GPINTENA
    WriteI2C(0x00); //GPINTENB
    WriteI2C(0x00); //DEFVALA
    WriteI2C(0x00); //DEFVALB
    WriteI2C(0x00); //INTCONA
    WriteI2C(0x00); //INTCONB
    WriteI2C(0b00001010); //IOCON
    WriteI2C(0b00001010); //IOCON
    WriteI2C(0x00); //GPPUA
    WriteI2C(0x00); //GPPUB
    WriteI2C(0x00); //INTFA
    WriteI2C(0x00); //INTFB
    WriteI2C(0x00); //INTCAPA
    WriteI2C(0x00); //INTCAPB
    WriteI2C(0x00); //GPIOA
    WriteI2C(0x00); //GPIOB    
    WriteI2C(0x00); //OLATA
    WriteI2C(0x00); //OLATB    
    I2C_STP();   
    
    Send_ConfigToRegister(IOCON, 0b00101010); //Config IOCON, no seq BANK=0
}

void Init_MCP23017(unsigned int addr){
    SetDeviceAdress(addr);
    I2C_INIT();
    I2C_CLEARBUS();
    ConfigDeviceFast();
}

void Send_ConfigToRegister(unsigned char reg, unsigned char cmd){
    DEVICE_ADRESS&=WBIT;
    I2C_STR();
    WriteI2C(DEVICE_ADRESS);
    WriteI2C(reg);
    WriteI2C(cmd);
    I2C_STP();    
}

char Read_NoSeqConfigFromRegister(){
    char data=0;
    
    DEVICE_ADRESS&=WBIT;
    I2C_STR();
    WriteI2C(DEVICE_ADRESS); //Write 
    
    DEVICE_ADRESS&=RBIT;
    I2C_STR();
    WriteI2C(DEVICE_ADRESS); //Read
    data=I2CRead(false);
    I2C_STP();
    
    return data;
}

char* Read_SeqConfigFromRegister(){
    char data[22];
    
    DEVICE_ADRESS&=WBIT;
    I2C_STR();
    WriteI2C(DEVICE_ADRESS); //Write 
    
    DEVICE_ADRESS&=RBIT;
    I2C_STR();
    WriteI2C(DEVICE_ADRESS); //Read
    for(int i=0;i<22;i++){
        data[i]=I2CRead(true);
    }
    I2C_STP();
    
    return data;
}

void Send_DataToPort(unsigned char port, unsigned char data){
    DEVICE_ADRESS&=WBIT;
    
    I2C_STR();
    WriteI2C(DEVICE_ADRESS);
    WriteI2C(port);
    WriteI2C(data);
    I2C_STP();
}

void Set_DirectionOfPort(unsigned char port, unsigned char dir){
    DEVICE_ADRESS&=WBIT;
    
    I2C_STR();
    WriteI2C(DEVICE_ADRESS);
    WriteI2C(port);
    WriteI2C(dir);
    I2C_STP();
}

#endif	/* MCP23017_FUNCTION */

