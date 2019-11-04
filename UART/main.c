/*
 * File:   main.c
 * Author: Nazim Bellabaci
 * Created on 20 juillet 2017, 09:57
 */


#include <xc.h>
#include "MyUart.h"
#pragma config FOSC = INTOSCCLK
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF      // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = ON          // Flash Program Memory Code Protection bit (0000h to 0FFFh code-protected (all protected))
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)
#define _XTAL_FREQ 8000000

char str[20];
int i=0;

void display(){
    for(int j=0;str[j]!='/';j++) UART_Write(str[j]);
     UART_Write('\n');    
}

void main() {
    //8mhz
    OSCCON=0x70;
    //max tune
    //OSCTUNE=0x1f;
   UART_init(9600);
   __delay_ms(100);
   
        //RCIF data available interupt 
   while(1){
	   
   if(RCIF){
       //UART_Read_Text(str,20);
       UART_ReadSentence(str,i);
       //UART_Write(str[i]);
       i++;
       UART_Write('\r');
       UART_Write('\r');
       UART_Write_Text(str);
                            
   } else {
       //UART_Write_Text("Yow\r");
       //UART_Write('\n');
   }
   
  __delay_ms(200);  
   /*for(int j=0;j<20;j++){
      // if(str[j]=='/'){
       if(str[j]=='\0'){
           display();
           break;
   }
   }*/
}
}   

void myRead(){
    char c=UART_Read();
        UART_Write(c);
        str[i]=c;
        i++;
        c=UART_Read();
        UART_Write(c);
        str[i]=c;
        i++;      
        UART_CorrectError(); 
}
void baudChange(){
        UART_init(9600);
        UART_Write_Text("Hello world\n"); 
        __delay_ms(4000);
        UART_init(57600);
        UART_Write_Text("Yo \n");
        __delay_ms(4000);
}

