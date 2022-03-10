#include "Configuracion.h"
#include "pinout.h"
#include <xc.h>
#include "LCD.h"
#include "keypad.h"
#include <pic18f4550.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "DHT11.h"

typedef char String[50];

#define ON 1
#define OFF 0

//void ControlTemperaturaVentilador(char *TempActual,int TempDigitada);
void ControlAspersor(char *HumedadActual,int HumedadDigitada);
void PedirDato(String Etiqueta,unsigned char vecLlenar[]);
void IniciarLed(bool TemperaturaAdecuada,bool HumedadAdecuada);
int TemperaturaDigitada(unsigned char prmTemperatura[]);
void CompararTempe(char *TempActual,char *HumActual,int TempDigitada,int HumDigitada);
void DatoSensorTH(char Datos[]);
void LedsIniciar();

void main(){
   
  
    Configuracion_Puertos_Leds = 0; //Configura el puerto de leds como salida
    LCD_Port=0x00;  // Confugura el puerto D como salida para la pantalla lcd
    bool flag = false;
    unsigned char Tempe[2];
    unsigned char Hume[2];
    char Datos[2];
    char Cadena[10];
    int indice = 0;
    int TempeAdecuada=0;
    int HumeAdecuada=0;
    
    
    
    
    OSCCON = 0x72;      //se configura el oscilador interno con frecuencia de 8 MHz.
    
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */  
    Confi_AspersoresVentiladores=0x00;
     RBPU=0;                             /* activate pull-up resistor */
     LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
     LedsIniciar();
    while(1){
     if(indice<2){  
       PedirDato("Tempe. Optima",Tempe);
       __delay_ms(100);
       PedirDato("Hume. Optima",Hume);
       indice = 2;
    }else{
        if(flag==false){
         TempeAdecuada = TemperaturaDigitada(Tempe); 
         HumeAdecuada =     TemperaturaDigitada(Hume);
        }
       flag=true;
    }
     if (flag==true){ 
        DatoSensorTH(Datos);
        CompararTempe(&Datos[0],&Datos[1],TempeAdecuada,HumeAdecuada); 
        ControlAspersor(&Datos[1],HumeAdecuada);
        
    /* convert humidity value to ascii and send it to display*/
    sprintf(Cadena,"%d",Datos[1]);
    LCD_String_xy(0,0,Cadena);
    sprintf(Cadena,".%d",0);
    LCD_Char('%');
    sprintf(Cadena,"  Hume.");
     LCD_String(Cadena);
    
    /* convert temperature value to ascii and send it to display*/
    sprintf(Cadena,"%d",Datos[0]);
    LCD_String_xy(2,0,Cadena);
    sprintf(Cadena,".%d",0);
    LCD_Char(0xdf);
    sprintf(Cadena,"C Tempe.");
    LCD_String(Cadena);

       __delay_ms(500);
     }
      
    }
    
}

void IniciarLed(bool TemperaturaOptima,bool HumedadOptima){
    LedsIniciar();
    if(TemperaturaOptima==false && HumedadOptima==false){
       Led_Rojo=ON; 
    }else if(TemperaturaOptima==false || HumedadOptima==false){
        Led_Amarillo=ON;
    }else{
        Led_Verde=ON;
    } 
}


int TemperaturaDigitada(unsigned char prmTemperatura[]){
    int Decena = 0;
    int Unidad = 0;
    int Resultado=0;
    Decena = prmTemperatura[0]-'0';
    Unidad = prmTemperatura[1]-'0';
    
    Decena = Decena * 10;
    Resultado = Decena + Unidad;
    
    return Resultado;
}


void CompararTempe(char *TempActual,char *HumActual,int TempDigitada,int HumDigitada){
    bool TemperaturaAdecuada= true;
    bool HumedadAdecuada =true;
    if(*TempActual<TempDigitada-2 || *TempActual >TempDigitada+2){
           TemperaturaAdecuada=false; 
    }
    if(*HumActual<HumDigitada-2 || *HumActual>HumDigitada+2){
        HumedadAdecuada=false;
    }
    
   IniciarLed(TemperaturaAdecuada,HumedadAdecuada);
}

void PedirDato(String Etiqueta,unsigned char vecLlenar[]){
     LCD_Clear();
     
     unsigned char tecla;
     LCD_String_xy(0,0,Etiqueta);
     LCD_Command(0xC0);  /* display pressed key on 2nd line of LCD */
     for(int i=0 ; i < 2 ; i++){
     tecla=keyfind();
     LCD_Char(tecla);
     vecLlenar[i] = tecla;
     }
     __delay_ms(100);
     LCD_Clear();
}

void DatoSensorTH(char Datos[]){
         char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
         char Checksum;
         DHT11_Start();                  // send start pulse to DHT11 module */
         DHT11_CheckResponse();          // wait for response from DHT11 module */
    
     //read 40-bit data from DHT11 module 
         RH_Integral = DHT11_ReadData(); // read Relative Humidity's integral value 
         RH_Decimal = DHT11_ReadData();  // read Relative Humidity's decimal value 
         T_Integral = DHT11_ReadData();  // read Temperature's integral value 
         T_Decimal = DHT11_ReadData();   // read Relative Temperature's decimal value 
         Checksum = DHT11_ReadData();    // read 8-bit checksum value
         
         Datos[0]=T_Integral;
         Datos[1]=RH_Integral;
}
void LedsIniciar(){
    Led_Amarillo=OFF;
    Led_Rojo=OFF;
    Led_Verde=OFF;
}
void ControlAspersor(char *HumedadActual,int HumedadDigitada){
    if(*HumedadActual<HumedadDigitada-2){
        Aspersor1=ON;
        
    }else{
        Aspersor1=OFF;
    }
}


/*
void ControlCalefactor(char *TempActual,int TempDigitada){
    if(*TempActual<TempDigitada+2){
        Calefactor1=ON;
        
    }else{
        Calefactor1=OFF;
        
    }    
}
*/








