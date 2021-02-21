/* 
 * File:  ADC.h  
 * Author: Ale Samayoa
 * Comments: Librería para el ADC
 * Revision history: 
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

//Ponemos el prototipo d ela función que vamos a poner en el .c de la libreria
void valADC (uint8_t a);

#endif 

