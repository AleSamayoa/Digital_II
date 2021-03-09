/*
 * File:   GIRO.c
 * Author: Ale Samayoa
 * Description: Libreria para el giroscopio GY 521
 * Created on 6 de marzo de 2021, 07:26 PM
 */
/* 
 * Se utilizó y se adaptaron las librerías de Khaled Magdy
 * de la página Deep Blue Embedded
 * Enlace: https://deepbluembedded.com
  */ 

#include "I2C.h"
#include "USART.h"
#include "GIRO.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Para iniciar el giroscopio 
void giro_init() {
    //Encendemos la comunicación I2C y la USART
    config_i2cmas(); 
    config_us(9600, 1); 
    //Iniciamos en esta dirección 
    i2c_init(0XD0);
    mas_write(0x6B); 
    mas_write(0x01);   
    stop();
    //Configuramos los datos de la comunicacion 
    i2c_init(0XD0);
    mas_write(0x00);
    stop();
    i2c_init(0XD0);
    mas_write(0x19);
    mas_write(0x08);
    stop();
    i2c_init(0XD0);
    mas_write(0x1A);
    mas_write(0x00);
    stop();
    
    //Para utilizar el giroscopio 
    i2c_init(0XD0);
    mas_write(0x1B);
    mas_write(0x00); 
    stop();
    //Para utilizar el acelemetrometro 
    i2c_init(0XD0);
    mas_write(0x1C);
    mas_write(0x00); 
    stop();

    return;

}

void giro_read(void) {
    //Para obtener los datos del giro, los almaceno en una variable
    //y los multiplico para poder utilizarlos 
    float fin[7];
    char* i;
    char val[14]; 
    int al[7];  
    i2c_init(0xD0);
    while (SSPCON2bits.ACKSTAT);
    mas_write(0x3B);
    while (SSPCON2bits.ACKSTAT);
    Rinit();
    mas_write(0xD1);

    for (int i = 0; i < 13; i++) val[i] = mas_read(0);
    val[13] = mas_read(1);
    stop();
  //Creo una tabla con los valores obtenidos 
    al[0] = ((int) val[0] << 8) | ((int) val[1]);
    al[1] = ((int) val[2] << 8) | ((int) val[3]);
    al[2] = ((int) val[4] << 8) | ((int) val[5]);
    al[3] = ((int) val[6] << 8) | ((int) val[7]);
    al[4] = ((int) val[8] << 8) | ((int) val[9]);
    al[5] = ((int) val[10] << 8) | ((int) val[11]);
    al[6] = ((int) val[12] << 8) | ((int) val[13]);

//Creo una tabla con los valores de la anterior como floats y multiplicadas para 
//que se puedan leer correctamente
    fin[0] = ((float) al[0]) * 0.0005982; 
    fin[1] = ((float) al[1]) * 0.0005982; 
    fin[2] = ((float) al[2]) * 0.0005982; 
    fin[3] = ((float) al[3]) / 340 + 36.53;
    fin[4] = ((float) al[4]) * 0.00763; 
    fin[5] = ((float) al[5]) * 0.00763;
    fin[6] = ((float) al[6]) * 0.00763;

    //El número se hace string para mandarlo por la UART 
    i = ftoa(fin[0], 2); 
    //Se manda el primer dato y así voy mandando todos 
    usart_string(i, 6); 
    i = ftoa(fin[1], 2);
    usart_string(" ", 10);
    usart_string(i, 6);

    i = ftoa(fin[2], 2);
    usart_string(" ", 10);
    usart_string(i, 6);

    i = ftoa(fin[3], 2);
    usart_string(" ", 10);
    usart_string(i, 6);

    i = ftoa(fin[4], 2);
    usart_string(" ", 10);
    usart_string(i, 6);
    
    i = ftoa(fin[5], 2);
    usart_string(" ", 10);
    usart_string(i, 6);

    i = ftoa(fin[6], 2);
    usart_string(" ", 10);
    usart_string(i, 6);

    usart_char('\n');

    return;
}
