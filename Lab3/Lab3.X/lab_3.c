/*
 * File:   lab_3.c
 * Author: Ale Samayoa
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Created on 31 de enero de 2020, 11:20 AM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "LCD.h"
#include "ADC.h"
#include "USART.h"
//****************************************************************
// CONFIGURACION
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#define _XTAL_FREQ 8000000

//******************************************************************************
// Variables
//******************************************************************************
uint8_t ADC1;
uint8_t ADC2;
uint8_t contador;
float v1=0.0;
float v2=0.0;
char valUSART =0;
char d[20];
//******************************************************************************
// Funciones
//******************************************************************************
void setup (void);
void __interrupt()ISR ();
float val(uint8_t b); 
void main(void);
//*****************************************************************************
void main(){
    setup();
    ADC_Init ();
    USART_In (9600);
    LCD_Init();
    Clear();
    while(1){
        ADC1= ADCval(0);
        ADC2= ADCval(1);
        v1= val(ADC1);
        v2= val(ADC2);
        Wr_USART_String("V1   V2   contador \n");
        sprintf(d, "%2.1f   %2.1f   %d", v1, v2, contador);
        Wr_USART_String(d);
        Wr_USART(13);
        Wr_USART(10);
        Clear();
        LCD_move_cursor (1,1);
        LCD_data_string("V1   V2   conta");
        LCD_move_cursor(2,0);
        LCD_data_string(d);
      __delay_ms(500);      
    }
    return;
}


//******************************************************************************
// Funciones
//******************************************************************************
void setup(void){
    ANSELH = 0;
    ANSEL  = 0;
    TRISA = 0;
    PORTA = 0;    
    TRISD = 0;
    PORTD = 0; 
    TRISE = 0;
    PORTE = 0;
//Para las interrupciones
 
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE   = 1;
    PIR1bits.RCIF   = 0;
    INTCONbits.GIE  = 1;
}

//para la conversion a decimales
float val(uint8_t b){
    return b*0.0196;
}

void __interrupt() ISR(){
    if (RCIF == 1){
        RCIF = 0;
        valUSART= Rd_USART();
        if (valUSART == '+'){contador++;}
        else if (valUSART== '-'){contador--;}    
    }
}
