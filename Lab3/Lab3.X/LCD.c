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
#include <xc.h> 
#include <stdint.h>
#include "LCD.h"
#define _XTAL_FREQ 8000000

void LCD_Init(void){
    TRISE = 0;       // Port Output for control pins
    TRISD = 0;       // Port output for Data pins
    __delay_ms(5);
    LCD_cmd (0x02);
    LCD_cmd (0x38);   // 8 bit mode, 5*7 matrix with 2 line
    LCD_cmd (0x0E);   // Display and cursor ON
    LCD_cmd (0x0C);   // clear LCD
    LCD_cmd (0x06);   // Move cursor to first line
}

void LCD_cmd (uint8_t cmd){
    RS = 0;
    RW = 0;
    LCD_datos(cmd);
    EN = 1;
    __delay_ms(10);
    EN = 0;
    __delay_ms(1);
    
}

void LCD_data(char data){
     RS = 1;
     RW = 0;
     LCD_datos(data);
     EN = 1;
     __delay_ms(10);
     EN = 0;
     __delay_ms(1);
}
void LCD_datos(uint8_t x){
    if (x & 1){D0 = 1;}else{D0 = 0;}
    if (x & 2){D1 = 1;}else{D1 = 0;}
    if (x & 4){D2 = 1;}else{D2 = 0;}
    if (x & 8){D3 = 1;}else{D3 = 0;}
    if (x & 16){D4 = 1;}else{D4 = 0;}
    if (x & 32){D5 = 1;}else{D5 = 0;}
    if (x & 64){D6 = 1;}else{D6 = 0;}
    if (x & 128){D7 = 1;}else{D7 = 0;}
}
void LCD_data_string(char *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_data(a[i]);
}


void LCD_move_cursor (uint8_t a, uint8_t b){
    uint8_t c;
    if(a == 1){
        c = 0x80;
        LCD_cmd(c);
    }
    else if (a == 2){
        a = 0xc0;
        LCD_cmd(c);  
    }
}

void Clear(void){
    LCD_cmd(0);
    LCD_cmd(1);
}
   
