/*
 * File:   s3.c
 * Author: Ale Samayoa
 * Description: Función del cuarto pic, s3
 * Created on 12 de febrero de 2021, 09:09 AM
 */
/* Diseñe e implemente una rutina para un microcontrolador en el cual utilice el
 *sensor de temperatura LM35. Adicionalmente ponga un semáforo dependiendo
 *del valor de temperatura según los siguientes rangos: t<25 verde, 25<t<36 amarillo,
 * y  t>36 rojo
 */
#include <xc.h>
#include <stdint.h>
#include "adc.h"

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

//******************************************************************************
///Variables y prototipos de funciones
//******************************************************************************

#define _XTAL_FREQ 4000000  

void setup(void);
void __interrupt()int1(void); 
uint8_t spidatos = 0;
uint8_t datos = 0; 

//******************************************************************************
//Loop principal 
//******************************************************************************

void main(void) {
    setup();        //Config puertos
    while (1) {
        adcon();
        //t<25°
        if (datos < 80) {
            PORTD = 0B00000100;
        //t>36
        } else if (datos > 91) {
            PORTD = 0B00000001;
        } else  {
            PORTD = 0B00000010;
        }
    }
}


//******************************************************************************
//Funciones
//******************************************************************************
void setup(void) {
    //Configuración de puertos
    TRISB &= 0B11111111; 
    TRISD &= 0; 
    ANSELH &= 0B00010000; 
    PORTD = 0; 
    PORTB = 0;
    // Configuración ADC en B0, justificado a la iz, con frecuencia Fosc/8
    ADCON0 = 0B01110000; 
    ADCON1 = 0B00010000; 
    ADCON0bits.ADON = 1; 
    // Configuración SPI como esclavo
    TRISA = 0B00100000; 
    TRISC = 0B00011000;
    SSPSTAT = 0B00000000; 
    SSPCON2 = 0; 
    SSPCON = 0B00110100;         
    // Configuración para interrupciones que harán el ADC
    PIE1 = 0B01001000; 
    PIR1bits.ADIF = 0; 
    INTCON = 0B11001000; 
}

void __interrupt() int1(void) {
    if (1 == ADIF) {
        valadc(&datos);
        ADIF = 0;
    }
    if (1 == SSPIF) {
        spidatos = SSPBUF;
        SSPBUF = datos;
        SSPIF = 0;
    }
}