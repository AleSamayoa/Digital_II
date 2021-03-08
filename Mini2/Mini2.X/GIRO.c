/*
 * File:   GIRO.c
 * Author: Ale Samayoa
 * Description: Libreria para el giroscopio GY 521
 * Created on 6 de marzo de 2021, 07:26 PM
 */
/* 
 * Se utilizó y se adaptaron las librerías de Khaled Magdy
 * de la página Deep Blue Embedded
 * Enlace: https://deepbluembedded.com/interfacing-i2c-lcd-16x2-tutorial-with-pic-microcontrollers-mplab-xc8/
  */ 

#include "I2C.h"
#include "USART.h"
#include "GIRO.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void giro_init() {

    config_i2cmas(); //se inicia el i2c
    config_us(9600, 1); //se inicia comunicación UART
    //    la mera direccion es 0xD0
    //    0xD1 para leer 
    //    0xD0 para escribir
    i2c_init(0XD0);
    mas_write(0x6B); // PWR_MGMT
    mas_write(0x01); //se escoge el reloj del giroscopio 8MHz  
    stop();

    //dato que se envia, pero no hace nada realmente
    //pero funciona
    i2c_init(0XD0);
    mas_write(0x00);
    stop();

    //  Sample rate 1kHZ
    i2c_init(0XD0);
    mas_write(0x19);
    mas_write(0x08);
    stop();

    //CONFIG
    i2c_init(0XD0);
    mas_write(0x1A);
    mas_write(0x00);
    stop();
    //Configuracion del giroscopio
    i2c_init(0XD0);
    mas_write(0x1B);
    mas_write(0x00); //+- 250 
    stop();
    //configuracion del acelerómetro
    i2c_init(0XD0);
    mas_write(0x1C);
    mas_write(0x00); //+-2g  
    stop();


    // PWR_MGMT2
    i2c_init(0X68);
    mas_write(0x6C);
    mas_write(0x00); //encendido 
    stop();

    return;

}

void giro_read(void) {
    float final[7];
    char* impresion;
    char val[14]; // final temporales
    int almacenar1[7]; // para almacenar1 final leídos 
    i2c_init(0xD0);
    while (SSPCON2bits.ACKSTAT);
    mas_write(0x3B);
    while (SSPCON2bits.ACKSTAT);
    Rinit();
    mas_write(0xD1);

    for (int i = 0; i < 13; i++) val[i] = mas_read(0);
    val[13] = mas_read(1);
    stop();

    almacenar1[0] = ((int) val[0] << 8) | ((int) val[1]);
    almacenar1[1] = ((int) val[2] << 8) | ((int) val[3]);
    almacenar1[2] = ((int) val[4] << 8) | ((int) val[5]);
    almacenar1[3] = ((int) val[6] << 8) | ((int) val[7]);
    almacenar1[4] = ((int) val[8] << 8) | ((int) val[9]);
    almacenar1[5] = ((int) val[10] << 8) | ((int) val[11]);
    almacenar1[6] = ((int) val[12] << 8) | ((int) val[13]);

 //los val por los que se multiplican fueron obtenidos de 

//al multiplicar por estos val lo que era raw data se convierte en final interpretables. 
    final[0] = ((float) almacenar1[0]) * 0.0005982; //Ax
    final[1] = ((float) almacenar1[1]) * 0.0005982; //Ay
    final[2] = ((float) almacenar1[2]) * 0.0005982; // Az
    final[3] = ((float) almacenar1[3]) / 340 + 36.53;
    final[4] = ((float) almacenar1[4]) * 0.00763; //velocidad angular en x, y z 
    final[5] = ((float) almacenar1[5]) * 0.00763;
    final[6] = ((float) almacenar1[6]) * 0.00763;

    //ftoa permite convertir un número a texto, se usa para poder mandarlo por uart
    impresion = ftoa(final[0], 2); //se guarda en un char con cantidad indefinida de final el float 
    usart_string(impresion, 6); //se manda el valor de la aceleración en x por uart, el valor ya fue convertido a decimal por ftoa
    // en las siguientes lineas se hace lo mismo pero para las diferentes cosas que lee el sensor
    impresion = ftoa(final[1], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);

    impresion = ftoa(final[2], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);

    impresion = ftoa(final[3], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);

    impresion = ftoa(final[4], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);
    impresion = ftoa(final[5], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);

    impresion = ftoa(final[6], 2);
    usart_string(" ", 10);
    usart_string(impresion, 6);

    usart_char('\n');

    return;
}
