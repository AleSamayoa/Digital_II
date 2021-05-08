//**************************************************************************************************************
// María Alejandra Samayoa Gómez
// Carnet 18064
// Electrónica Digital II
//**************************************************************************************************************

//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"

#define XTAL 16000000

//**************************************************************************************************************
// Variables y definiciones de pines
//**************************************************************************************************************
uint32_t i = 0;
#define R GPIO_PIN_1
#define V GPIO_PIN_3
#define A GPIO_PIN_1|GPIO_PIN_3
#define O 0x00000000
//**************************************************************************************************************
// Prototipos de Funciones
//**************************************************************************************************************
void delay(uint32_t msec);
void delay1ms(void);

//**************************************************************************************************************
// Parte 2
//**************************************************************************************************************
int main(void)
{
    //Seteando la frecuencia del reloj a diferentes valores
    //SysCtlClockSet(SYSCTL_SYSDIV_2 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_32MHZ);  //32MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);  //16MHz

    // Configuración del reloj para que esté en F y los pines para los leds y push
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

   //**********************************************************************************************************
   // Loop Principal
   //**********************************************************************************************************
   while (1) {

       //Si se presiona el boton
       if ( !GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) )  {
           //Se enciende en Verde
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, V);
           SysCtlDelay(delay);

           //Parpadeo 3 veces
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, V);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, O);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, V);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, O);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, V);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, O);
           SysCtlDelay(delay/4);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, O);
           SysCtlDelay(delay/2);

           // Cambia a amarillo
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, A);
           SysCtlDelay(delay);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, O);
           SysCtlDelay(delay/2);

           // Cambio a rojo
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, R);
           SysCtlDelay(delay);
       }

    }
}
//**************************************************************************************************************
// Funciones
//**************************************************************************************************************
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}
//Desde la página 140, se obtiene esta manera de hacer un delay
void delay1ms(void)
{
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);

}
