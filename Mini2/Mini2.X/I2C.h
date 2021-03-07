/* 
 * File:  usart.h
 * Author: Ale Samayoa
 * Comments: Librer�a para la comunicaci�n usart
 * Revision history: 
 */
/* 
 * Se utiliz� y se adaptaron las librer�as de Khaled Magdy
 * de la p�gina Deep Blue Embedded
 * Enlace: https://deepbluembedded.com/interfacing-i2c-lcd-16x2-tutorial-with-pic-microcontrollers-mplab-xc8/
  */ 
#ifndef I2C_H
#define I2C_H

#define _XTAL_FREQ             4000000

#define baudrate           100000
#define SCL_D                  TRISC3
#define SDA_D                  TRISC4

//-----------[ Functions' Prototypes ]--------------

//---[ I2C Routines ]---

void config_i2cmas();
void wait();
void mas_init();
void i2c_init(char d);
void Rinit();
void stop();
void ack_i2c();
void nack_i2c();
unsigned char mas_write(unsigned char data);
unsigned char mas_readbyte();
unsigned char mas_read(unsigned char);


#endif

