/*
 * File:   mas.c
 * Author: Ale Samayoa
 * Description: Función del primer pic, mas
 * Created on 12 de febrero de 2021, 09:08 AM
 */
/* 
 * Diseñe e implemente la comunicación SPI entre el microcontrolador maestro 
 * y los 3 esclavos, desplegar los resultados en una pantalla LCD 16x2 e
 * implemente  la  comunicación  USART  conla  terminal  virtual,  de  tal  
 * forma  que aparezcan los valores actuales de cada una de las variables 
 */

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

//Vamos a incluir una librería para la LCD y la comunicación USART
#include <xc.h>
#include <stdint.h>
#include "usart.h"
#include "lcd.h"
#define _XTAL_FREQ 4000000 
//******************************************************************************
//  Variables y prototipos de funciones
//******************************************************************************
void setup(void);
void __interrupt()int1(void);
void mostrar_titulo_lcd(void);
void encabezado_usart(void);
void mostrar_dato(void);

uint8_t pot = 0;
uint8_t cont = 0;
uint8_t temp = 0;
//******************************************************************************
// Loop principal 
//******************************************************************************

void main(void) {
    setup();
    LCD_Init(); // INICIALIZA LA PANTALLA
    while (1) {
        encabezado_usart();
        mostrar_titulo_lcd();
        mostrar_dato();
        __delay_ms(2);
        PORTBbits.RB7 = 0;
        SSPBUF = 255;

        tnl_usart();
    }
}

//******************************************************************************
//Funciones
//******************************************************************************
//Función de Setup para definir los puertos, configurar adc, interrupciones y spi
void setup(void) {
    //Configuración de puertos
    ANSELH = 0; 
    TRISD = 0; 
    PORTD = 0; 
    PORTC = 0;
    // Configuración de la USART
    config_us(); 
    // Configuración SPI como master
    TRISB = 0B00011111; 
    PORTB = 0B01100000; 
    TRISC = 0B00010000; 
    SSPSTAT = 0B00000000; 
    SSPCON2 = 0; 
    SSPCON = 0B00110000;   
    // Configuración para interrupciones
    PIE1 = 0B00001000; 
    INTCON = 0B11000000; 
}

void mostrar_titulo_lcd(void) { // MUESTRA EN LA PANTALLA EL ENCABEZADO
    LCD_move_cursor(1, 1);
    LCD_data_string("S1:   S2:   S3: ");
}

void encabezado_usart(void) {
//Datos S1
    __delay_ms(2);
    tvirt_usart(83);
    __delay_ms(2);
    tvirt_usart(49);
    __delay_ms(2);
    tvirt_usart(58);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
//Datos S2
    tvirt_usart(83);
    __delay_ms(2);
    tvirt_usart(50);
    __delay_ms(2);
    tvirt_usart(58);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);

//Datos S3
    tvirt_usart(83);
    __delay_ms(2);
    tvirt_usart(51);
    __delay_ms(2);
    tvirt_usart(58);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);
    tnl_usart();
    __delay_ms(2);

}

void mostrar_dato(void) {
    LCD_move_cursor(2, 1);
    LCD_data_char(pot);
}

//******************************************************************************
//                          INTERRUPCION
//******************************************************************************

void __interrupt()int1(void) {
    GIE = 0; 
    if (SSPIF) {
        pot = SSPBUF; 
        PORTBbits.RB7 = 1;
        SSPIF = 0;
    }

    GIE = 1; 
}