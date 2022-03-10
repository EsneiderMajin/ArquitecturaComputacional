/* 
 * File:   pinout.h
 * Author: Equipo
 * Created on 2 de marzo de 2022, 19:56
 */
   
#ifndef PINOUT_H
#define	PINOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

//Configuracion ventiladores y aspersores
#define Confi_AspersorCalefactor TRISC  
// ASPERSORES
#define Aspersor LATC0


//Configuracion Sensor Temperatura y humedad DHT11
#include "Configuracion.h"
#define Data_Out LATA0              // assign Port pin for data/
#define Data_In PORTAbits.RA0       // read data from Port pin/
#define Data_Dir TRISAbits.RA0      // Port direction 
    
// ASPERSOR   
#define Aspersor LATC0

//Calefactor
#define Calefactor LATC7
    

//Configuracion Puerto E para Leds.    
#define Configuracion_Puertos_Leds TRISE
#define Led_Rojo LATE0
#define Led_Amarillo LATE1
#define Led_Verde LATE2
    
//CONFIGURACION PINS DEL LCD

#define RS LATD0                    /*PIN 0 of PORTB is assigned for register select Pin of LCD*/
#define EN LATD1                    /*PIN 1 of PORTB is assigned for enable Pin of LCD */
#define ldata LATD                  /*PORTB(PB4-PB7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD
    
//CONFIGURACION PONS DEL TECLADO
    
#define write_port LATA  /* latch register to write data on port */
#define read_port PORTB  /* PORT register to read data of port */
#define Direction_Port TRISA

#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */

