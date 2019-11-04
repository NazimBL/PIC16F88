/*
 * Author: Nazim BL
 * MPLAB X IDE
 * Created on 30 juin 2017, 17:09
 */
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB3      // CCP1 Pin Selection bit (CCP1 function on RB3)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

#include <xc.h>
#define _XTAL_FREQ 20000000

//TIMER0    8-bit    $$RegValue = 256-((Delay * Fosc)/(Prescalar*4))  delay in sec and Fosc in hz  
//FORMULA to calculate Delay
//Delay = ((256-REG_val)*(Prescal*4))/Fosc
char hscnd = 0;
int count = 0;
char get_scnds =0;
char flag =0;
char i=0;
char tag=0;

void interrupt timer_isr()
{  
    if(TMR0IF==1) // Timer flag has been triggered due to timer overflow
    {
        TMR0 = 100;     //Load the timer Value
        TMR0IF=0;       // Clear timer interrupt flag
        count+=1;
    } 
    
    if (count == 250){
        hscnd+=1;
        count=0;
        tag+=1;
    }   
}
void main(void) {
	
    OPTION_REG = 0b00000001;  // Timer0 with external freq and 64 as prescalar // Also Enables PULL UPs
    TMR0=100;       // Load the time value for 0.0019968s; delayValue can be between 0-256 only
    ANSEL=0;
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    
    TRISB=0x01;
     while(1)
    {
        count =0; //Do not run timer while in main loop
        
        //*******Get the number delay from user****//////
        if (RB0==1 && flag==0) //When input given
        {
            get_scnds+=1; //get_scnds=get_scnds+1//Increment variable 
            flag=1;
        }
        if (RB0==0) flag=0;
       
        
       
                   if(tag%2==0)PORTB=0x04;
                   else PORTB=0x00;// i+=1; //Move to next LED after the defined Delay
                   flag=2;
        }
        if (flag==2) //Reset timer if button is high again
        {
            get_scnds=0;hscnd=0;i=0;  
            PORTB=0; //Turn off all LEDs
        }    
    return;
}
