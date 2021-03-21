/* 
 * File:  I2C.c
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación I2C
 */
/* 
 * Se utilizó y se adaptaron las librerías de Khaled Magdy
 * de la página Deep Blue Embedded
 * Enlace: https://deepbluembedded.com
  */ 

#include <xc.h>
#include "I2C.h"

//Configuración i2c como master
void config_i2cmas()
{
  SSPCON  = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/baudrate) - 1;
  SCL_D = 1;
  SDA_D = 1; 
}
//Espera hasta que se ya no hayan datos que se esten mandando
void wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
//Se inicia ya el proceso como masterdespues de esperar
void mas_init()
{
    wait();
    SEN = 1;
}
//Empieza la comunicación 
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
//Manda los datos ACK
void ack_i2c(void)
{
	ACKDT = 0;			
    ACKEN = 1;			
    while(ACKEN);
}
//Manda los datos NACK
void nack_i2c(void)
{
	ACKDT = 1;			
	ACKEN = 1;			
    while(ACKEN);
}
//Se mandan los datos por el buffer
unsigned char mas_write(unsigned char data)
{
    wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}
//Se reciben los datos 
unsigned char mas_readbyte(void)
{
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
