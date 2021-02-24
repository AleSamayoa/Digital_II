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
void s1spi(void);
void s2spi(void);
void s3spi(void);
void titulo(void);
void header(void);
void show(void);

void map_var(uint8_t v_in, uint8_t *v_out, uint8_t inMin, uint8_t inMax,
        uint8_t outMin, uint8_t outMax);
void voltaje(uint8_t data_in, uint8_t *volt_u, uint8_t *volt_d1,
        uint8_t *volt_d2);
void conts(uint8_t data_in, uint8_t *uni, uint8_t *dec, uint8_t *cent);

uint8_t pot = 39, cont = 39, temp = 0;

uint8_t pot_u = 0, pot_d1 = 0, pot_d2 = 0, temp_m = 0, cont_u = 0, cont_d = 0,
        cont_c = 0, aux = 0;
char sdata;
//******************************************************************************
// Loop principal 
//******************************************************************************

void main(void) {
    setup();
    LCD_Init(); // INICIALIZA LA PANTALLA
    header();
    while (1) {
        s1spi();
        __delay_ms(5);
        s2spi();
        __delay_ms(5);
        s3spi();
        __delay_ms(5);
        map_var(temp, &temp_m, 0, 255, 13, 150);
        voltaje(pot, &pot_u, &pot_d1, &pot_d2);
        titulo();
        show();

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
    ANSEL = 0;
    TRISA = 0;
    TRISC = 0;
    TRISD = 0; 
    PORTA = 0; 
    PORTC = 0; 
    PORTD = 0;
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

void titulo(void) { 
    LCD_move_cursor(1, 1);
    LCD_data_string("S1:   S2:   S3: ");
}

void header(void) {
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
//Las siguientes funciones sacan los datos del SPI
void s1spi(void) { 
    PORTBbits.RB5 = 0;
    __delay_ms(1);
    SSPBUF = 0;
}

void s2spi(void) {
    PORTBbits.RB6 = 0;
    __delay_ms(1);
    SSPBUF = 0;
}
void s3spi(void) { 
    PORTBbits.RB7 = 0;
    __delay_ms(1);
    SSPBUF = 0;
}
void show(void) {
    LCD_move_cursor(2, 1);
    //S1
    n_ascii(pot_u, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    LCD_data_char(46); 
    tvirt_usart(46);
    __delay_ms(2);
    n_ascii(pot_d1, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    n_ascii(pot_d2, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    LCD_data_char(86);
    tvirt_usart(86);
    __delay_ms(2);
    LCD_data_string("  "); 
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);

    // S2
    conts(cont, &cont_u, &cont_d, &cont_c);
    n_ascii(cont_c, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    n_ascii(cont_d, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    n_ascii(cont_u, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    LCD_data_string("  "); 
    tvirt_usart(32);
    __delay_ms(2);
    tvirt_usart(32);
    __delay_ms(2);

    // S3
    conts(temp_m, &cont_u, &cont_d, &cont_c);
    n_ascii(cont_c, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    n_ascii(cont_d, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    n_ascii(cont_u, &sdata);
    LCD_data_char(sdata);
    tvirt_usart(sdata);
    __delay_ms(2);
    LCD_data_char(67);
    tvirt_usart(67);
    __delay_ms(2);
}
//Se utilizó y se adaptaron las librerías de Ligo George 
//*de la página https://deepbluembedded.com/map-function-embedded-c/
//*Enlace: https://deepbluembedded.com/map-function-embedded-c/

void map_var(uint8_t v_in, uint8_t *v_out, uint8_t inMin, uint8_t inMax,
        uint8_t outMin, uint8_t outMax) {
    *v_out = ((((v_in - inMin)*(outMax - outMin)) / (inMax - inMin)) + outMin);
}

void voltaje(uint8_t data_in, uint8_t *volt_u, uint8_t *volt_d1, uint8_t *volt_d2) {
    while (data_in > 49) { // DIVIDE ENTRE 50
        data_in = data_in - 50;
        aux++; // PARA OBTENER VALORES ENTRE 0 Y 5    
    }
    *volt_u = aux;
    aux = 0;

    while (data_in > 9) { 
        data_in = data_in - 10;
        aux++; 
    }
    *volt_d1 = aux;
    *volt_d2 = data_in; 
    aux = 0;
}

void conts(uint8_t data_in, uint8_t *uni, uint8_t *dec, uint8_t *cent) {

    while (data_in > 99) { 
        data_in = data_in - 100;
        aux++;   
    }
    *cent = aux;
    aux = 0;

    while (data_in > 9) { 
        data_in = data_in - 10;
        aux++; 
    }
    *dec = aux;
    *uni = data_in;
    aux = 0;
}
//******************************************************************************
//                          INTERRUPCION
//******************************************************************************

void __interrupt()int1(void) {
    GIE = 0; 
    if (1 == SSPIF) {
        if (0 == PORTBbits.RB7) { 
            PORTBbits.RB7 = 1;
            pot = SSPBUF;
        } else if (0 == PORTBbits.RB6) {
            PORTBbits.RB6 = 1;
            cont = SSPBUF;
        } else if (0 == PORTBbits.RB5) {
            PORTBbits.RB5 = 1;
            temp = SSPBUF;
        }
        SSPIF = 0;
    }

    GIE = 1; 
}