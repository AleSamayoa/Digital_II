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
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

#define XTAL 16000000
//**************************************************************************************************************
// Variables y definiciones de pines
//**************************************************************************************************************

uint32_t periodo;
char datos = ' ';
uint8_t v = 0;
//**************************************************************************************************************
// Prototipos de Funciones
//**************************************************************************************************************
void initUART(void);


//**************************************************************************************************************
// Parte 2
//**************************************************************************************************************
int main(void){
    //Seteando la frecuencia del reloj
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);  //16MHz

    // Configuración del reloj para que esté en F y los pines para los leds
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    initUART();

    //TIMER0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //TIMER0 periodico
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Periodo= 0.5 s
    periodo = (SysCtlClockGet()) / 4;

    // Periodo del temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, periodo - 1);

    // Interrupción por el TIMER0A
    IntEnable(INT_TIMER0A);

    // Interrupción timeout habilitada
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Interrupciones globales habilitadas
    IntMasterEnable();

    //TIMER HABILITADO
    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
            if (datos != ' ' && v) {
                if (datos == 'r') {
                    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1)){
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                            }
                            else {
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
                            }
                }

                if (datos == 'g') {
                    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3)){
                         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                            }
                    else {
                         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
                            }

                }
                if (datos == 'b')   {
                    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2)){
                               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                           }
                           else {
                               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
                           }
                }

                datos = ' ';
            }
        }

}
//**************************************************************************************************************
// Funciones
//**************************************************************************************************************

//Se inicializa la UART
void initUART(void)
{
    //GPIO port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Peripehral UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //Pins peripheral controlled
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //Configuración UART: 115200, 8 data bits, 1 stop bit, none parity
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Limpiamos banderas
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR);

    //Se inicia la UART y las interrupciones
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

}

//Interrupción del TIMER 0
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    v = ~v;

}

//Interrupción del UART0
void UARTIntHandler(void){

    //Clear the UART interrupt
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);

    datos = UARTCharGet(UART0_BASE);

}

