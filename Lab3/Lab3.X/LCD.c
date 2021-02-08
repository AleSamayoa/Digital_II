//Aquí configuramos el display de la LCD
//Me voy a guiar con el ejemplo de electrosome

/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome
#include <stdint.h> 
#include <pic16f887.h>
#include "LCD.h"
#define _XTAL_FREQ 8000000


void LCD_cmd (char cmd){
    LCD_datos = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(10);
    EN = 0;
    __delay_ms(1);
    
}

void LCD_data (char data){
     LCD_datos = data;
     RS = 1;
     RW = 0;
     EN = 1;
     __delay_ms(10);
     EN = 0;
     __delay_ms(1);
    
}

void LCD_data_string(char* string){
    int index;
    for(index =0;index<16;index++) {
        if(string[index] == '\0')
            break;
        LCD_datos=(string[index]);
    }
}

void LCD_move_cursor (char line){
    char addr;
    if(line == 1)
        addr = 0x80;
    else
        addr = 0xc0;
    LCD_cmd (addr);    
}
   

void LCD_Init(void)
{
    TRISE = 0;       // Port Output for control pins
    TRISD = 0;       // Port output for Data pins
    __delay_ms(5);
    LCD_cmd (0x38);   // 8 bit mode, 5*7 matrix with 2 line
    LCD_cmd (0x0E);   // Display and cursor ON
    LCD_cmd (0x01);   // clear LCD
    LCD_cmd (0x80);   // Move cursor to first line
    }



