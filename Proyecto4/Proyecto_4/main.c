//**************************************************************************************************************
// María Alejandra Samayoa Gómez
// Carnet 18064
// Electrónica Digital II
//**************************************************************************************************************

//**************************************************************************************************************
// Librerias
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
#include "inc/hw_gpio.h"


#define XTAL 16000000

#define GPIO_PD6_U2RX           0x00031801
#define GPIO_PD7_U2TX           0x00031C01


//**************************************************************************************************************
// Variables
//**************************************************************************************************************
uint32_t        i = 0;
uint32_t        ui32Period;
uint32_t        data = 0;
unsigned char   datos=0;
uint8_t         par1 = 0;
uint8_t         par2 = 0;
uint8_t         par3 = 0;
uint8_t         par4 = 0;
bool            par1s = false;
bool            par2s = false;
bool            par3s = false;
bool            par4s = false;
bool            par1o=false;
bool            par2o=false;
bool            par3o=false;
bool            par4o=false;

//**************************************************************************************************************
// Prototipos
//**************************************************************************************************************

void initUART(void);
void setup(void);
void mandar_datos(void)


//**************************************************************************************************************
// Loop Principal
//**************************************************************************************************************
int main(void){
    //Configuración
    setup();

    while (1)    {
       //Miramos el estado de los botones
       par1 = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);
       par2 = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1);
       par3 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);
       par4 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);
       //Como los state de los parqueos son bools, si los botones estan encendidos serán true
       par1s = (par1==0);
       par2s = (par2==0);
       par3s = (par3==0);
       par4s = (par4==0);

       //El estado de inicio
       //Las luces verdes encendidas
       GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);
       GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6);
       GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
       GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
       //Las rojas apagadas
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);

       //Las flags de ocupado empiezan apagadas
       par1o=false;
       par2o=false;
       par3o=false;
       par4o=false;

       //Si el estado es verdadero empiezan los ifs
        if (par1s){
               //Si esta ocupado, encendemos la luz roja y apagamos luz verde, encendemos las flags
               GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7 , GPIO_PIN_7);
               GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
               par1o= true;
           }
           if (par2s){
               //Si esta ocupado, encendemos la luz roja y apagamos luz verde
               GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6 , GPIO_PIN_6);
               GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0);
               par2o= true;
           }

           if (par3s){
               //Si esta ocupado, encendemos la luz roja y apagamos luz verde
               GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5 , GPIO_PIN_5);
               GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
               par3o= true;
           }

           if (par4s){
               //Si esta ocupado, encendemos la luz roja y apagamos luz verde
               GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 , GPIO_PIN_4);
               GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
               par4o=true;
           }
           if (datos==1){
               datos=0;
               mandar_datos();
           }

       }

}


//**************************************************************************************************************
// Inicialización de UART
//**************************************************************************************************************
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

    //Iniciamos también el Uart2
    HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE+GPIO_O_CR) |= GPIO_PIN_7;

    //Lo habilitamos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    //HWREG(GPIO_PORTD_BASE,);

    //Los pines D6 y D7 van a ser los pines
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    //Configuración UART: 115200, 8 data bits, 1 stop bit, none parity
    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Limpiamos banderas
    UARTIntClear(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR);

    //RX y TX en D6 y D7
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);


}

//Interrupción del TIMER 0
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    datos=1;

}

//Interrupción del UART0
void UARTIntHandler(void){
    //Clear interrupt
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    data = UARTCharGet(UART0_BASE);
    UARTCharPut(UART0_BASE, receive); //enviamos el caracter como prueba

}

void setup(void){
    // Se setea oscilador externo de 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);  //Reloj configurado a 40MHz
    //*************************************************************************************************************************

    //Botones
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //Botones parqueo 1 y 2 en B0 y B1, como outputs y weak pullup
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //Botones parqueo 3 y 4 en E4 y E5, como outputs y weak pullup
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //LEDS
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //Luces rojas en C4, C5, C6, y C7
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    //Luces verdes en B4, B5, B6 y B7
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    //UART
    initUART();

    //*************************************************************************************************************************
    //Configuración del timer 0
    //*************************************************************************************************************************s

    // Se habilita el reloj para el timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configuración del Timer 0 como temporizador períodico
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Se calcula el período para el temporizador (1 seg) este período es el que se utiliza para actualizar los datos en el servidor web
    ui32Period = (SysCtlClockGet()/4);
    // Establecer el periodo del temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

    // Se habilita la interrupción por el TIMER0A
    IntEnable(INT_TIMER0A );
    // Se establece que exista la interrupción por Timeout
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Se habilitan las interrupciones Globales
    IntMasterEnable();
    // Se habilita el Timer
    TimerEnable(TIMER0_BASE, TIMER_A);
}

//Se mandan por la UART las banderas de ocupado
void mandar_datos(void){
    UARTCharPut(UART2_BASE, num2string(par1o));
    UARTCharPut(UART2_BASE, num2string(par2o));
    UARTCharPut(UART2_BASE, num2string(par3o));
    UARTCharPut(UART2_BASE, num2string(par4o));

}
