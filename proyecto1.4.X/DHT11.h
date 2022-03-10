/* 
 * File:   DHT11.h
 * Author: Equipo
 *
 *  Created on 3 de marzo de 2022, 15:21
 */



#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();


#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */

