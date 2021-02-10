/*
 * File: LCD.h  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  

//Esto sirve como progra defensiva por si no estan definidas las variables
//Vamos a hacer algunos prototipos de funciones aquí también
#ifndef LCD_H
#define	LCD_H
#include <xc.h>
#include <stdint.h>
//***************************************************************************
//variables
//***************************************************************************
#ifndef RS
#define RS RE0
#endif

#ifndef RW
#define RW RE1
#endif

#ifndef EN
#define EN RE2
#endif

#ifndef D0
#define D0 RD0
#endif

#ifndef D1
#define D1 RD1
#endif

#ifndef D2
#define D2 RD2
#endif

#ifndef D3
#define D3 RD3
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif



void LCD_Init(void);
void LCD_cmd (uint8_t cmd);
void LCD_data (char data);
void LCD_datos(uint8_t x);
void LCD_data_string(char *a);
void LCD_move_cursor(uint8_t a, uint8_t b);
void Clear (void);


#endif	/* LCD_H */

