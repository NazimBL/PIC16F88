/*
 * File:   main.c
 * Author: Nazim
 *
 * Created on 29 juin 2017, 16:41
 */

// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)


#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#define _XTAL_FREQ 2000000

void sequence_blink(int get) {
	
  for (int i=1; i<=7 && RB0==1; i++){
       PORTB = get << i;  //LED move Left Sequence 
       __delay_ms(50);
        }
          for(int i=7; i>=1 && RB0==1; i--){
       PORTB = get << i;  //LED move Left Sequence 
       __delay_ms(50);
        }  
}

void main(void) {
    
	ANSEL=0;
    TRISB=0x01;
    PORTB=0;
        
    while(1){
		
        if(RB0==1){
            sequence_blink(1);
            sequence_blink(3);            
        }
        else PORTB=0xff;  
    }
    return;
}
