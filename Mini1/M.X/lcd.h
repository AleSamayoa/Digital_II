/* 
 * File: lcd.h
 * Author: Ale Samayoa
 * Comments:Libreria para hacer funcionar la pantalla LCD
 * Revision history: 
 */
/* 
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
  */

// This is a guard condition so that contents of this file are not included
// more than once.  
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void LCD_Init(void);
void LCD_datos(char a);
void LCD_cmd(char a);
void Clear(void);
void LCD_move_cursor(uint8_t a, uint8_t b);
void LCD_data_char(char a);
void LCD_data_string(char *a);
void shift_right(void);
void shift_left(void);


#endif	/* XC_HEADER_TEMPLATE_H */

