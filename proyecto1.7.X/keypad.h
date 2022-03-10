/* 
 * File:   keypad.h
 * Author: Equipo
 *
 * Created on 3 de marzo de 2022, 18:20
 */

#ifndef KEYPAD_H
#define	KEYPAD_H


#ifdef	__cplusplus
extern "C" {
#endif
#include "Configuracion.h"

#define PB7     7 
#define PB6     6
#define PB5     5
#define PB4     4
#define RA6     3
#define RA5     2
#define RA4     1
#define RA3     0

/* FILAS-SALIDAS */
#define ROW1   RA3
#define ROW2   RA4
#define ROW3   RA5
#define ROW4   RA6

/* COLUMNAS-ENTRADAS */
#define COL1   PB4
#define COL2   PB5
#define COL3   PB6
#define COL4   PB7

#define PTECLADO  TRISA
#define FILAS     LATA
#define COLUMNAS  PORTB


#include "conectores.h"
    
void keypad_init (void);
char keypad_getkey(void);
unsigned char keyfind();  /* function to find pressed key */

short readKeypad();  //Scan the Keypad
char decodeCharacter(short a);  //Convert keypad value to character

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

