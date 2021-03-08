/*
 * File:   GIRO.h
 * Author: Ale Samayoa
 * Description: Libreria para el giroscopio GY 521
 * Created on 6 de marzo de 2021, 07:26 PM
 */
#ifndef GIRO_H
#define	GIRO_H

#include <xc.h>
#include <stdint.h>


void giro_init(void);
void giro_read();

#endif	/* GY-521_H*/

