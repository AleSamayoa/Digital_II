/* 
 * File: lcd.c
 * Author: Ale Samayoa
 * Comments:Libreria para hacer funcionar la pantalla LCD
 * Revision history: 
 */
/* 
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
  */


#include <xc.h>
#include <stdint.h>
#include "lcd.h"

#define _XTAL_FREQ 8000000

#define RS RC1
#define EN RC0
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void LCD_Init(void) { 
    LCD_datos(0x00); 
    __delay_ms(20);
    LCD_cmd(0x30);
    __delay_ms(5);
    LCD_cmd(0x30);
    __delay_ms(15);
    LCD_cmd(0x30);
    LCD_cmd(0x38); 
    LCD_cmd(0x0C);  
    LCD_cmd(0x06); 
}

void LCD_datos(char a) { 
    if (a & 1)  
        D0 = 1;
    else
        D0 = 0;
    if (a & 2)
        D1 = 1;
    else
        D1 = 0;
    if (a & 4)
        D2 = 1;
    else
        D2 = 0;
    if (a & 8)
        D3 = 1;
    else
        D3 = 0;
    if (a & 16)
        D4 = 1;
    else
        D4 = 0;
    if (a & 32)
        D5 = 1;
    else
        D5 = 0;
    if (a & 64)
        D6 = 1;
    else
        D6 = 0;
    if (a & 128)
        D7 = 1;
    else
        D7 = 0;
}

void LCD_cmd(char a) { 
    RS = 0; 
    LCD_datos(a);
    EN = 1; 
    __delay_ms(10);
    EN = 0; 
}

void Clear(void) {
    LCD_cmd(0);
    LCD_cmd(1);
}

void LCD_move_cursor(uint8_t a, uint8_t b) {  
    char temp, x, y;
    if (a == 1) { 
        temp = 0x80 + b - 1; 
        LCD_cmd(temp); 
    } 
    else if (a == 2) { 
        temp = 0xC0 + b - 1;
        LCD_cmd(temp); 
    }
}



void LCD_data_char(char a) { 
    RS = 1;
    LCD_datos(a); 
    EN = 1;
    __delay_us(40); 
    EN = 0;     
}

void LCD_data_string(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        LCD_data_char(a[i]); 
}

void shift_right(void) {
    LCD_cmd(0x1C); 
}

void shift_left(void) {
    LCD_cmd(0x18); 
}



