/* 
 * File:  I2C.c
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación I2C
 */
/* 
 * Se utilizó y se adaptaron las librerías de Khaled Magdy
 * de la página Deep Blue Embedded
 * Enlace: https://deepbluembedded.com/interfacing-i2c-lcd-16x2-tutorial-with-pic-microcontrollers-mplab-xc8/
  */ 

#include <xc.h>
#include "I2C.h"

void config_i2cmas()
{
  SSPCON  = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/baudrate) - 1;
  SCL_D = 1;
  SDA_D = 1; 
}

void wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void mas_init()
{
    wait();
    SEN = 1;
}

void i2c_init(char d)
{
    wait();
    SEN = 1;
    mas_write(d);
}

void Rinit()
{
    wait();
    RSEN = 1;
}

void stop()
{
    wait();
    PEN = 1;
}

void ack_i2c(void)
{
	ACKDT = 0;			// 0 -> ACK
    ACKEN = 1;			// Send ACK
    while(ACKEN);
}

void nack_i2c(void)
{
	ACKDT = 1;			// 1 -> NACK
	ACKEN = 1;			// Send NACK
    while(ACKEN);
}

unsigned char mas_write(unsigned char data)
{
    wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}

unsigned char mas_readbyte(void)
{
    //---[ Receive & Return A Byte ]---
    wait();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSPIF);	  // Wait Until Completion
	SSPIF = 0;		  // Clear The Interrupt Flag Bit
    wait();
    return SSPBUF;	  // Return The Received Byte
}

unsigned char mas_read(unsigned char an)
{   wait();
    //---[ Receive & Return A Byte & Send ACK or NACK ]---
    unsigned char data;
    RCEN = 1;              
    while(!BF);      
    data = SSPBUF;           
    if(an==0)
        ack_i2c();            
    else
        nack_i2c();     
    while(!SSPIF);                 
    SSPIF=0;   
    return data;
}
