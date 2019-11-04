
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>


#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON     // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)
#define iff_slave 0x0A
#define _XTAL_FREQ 20000000


char message;
short z;


void initialize_i2c(){
    //set all state register values to zero ( initial value to avoid overflow and colision errors)
    SSPSTAT=0x00;
    //receive flag
    SSPIF=0;
    /* configuration register :( from msb to lsb )
     * 0011 0110 = 36( hex )
     Wcol=0 colision bit
     sspov=0 overflow 
     sspen=1 enable ssp
     ckp=1 clock
     sspm = ssp mode = 6 = 0110
    */SSPCON=0x36;        
}

void interrupt I2C_Slave_Read()
{ 
    if(SSPIF == 1)
    {
       SSPCONbits.CKP = 0;
       
       if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))
       {
             z = SSPBUF;            // Read the previous value to clear the buffer
             SSPCONbits.SSPOV = 0; // Clear the overflow flag
             SSPCONbits.WCOL = 0;   // Clear the collision bit
             SSPCONbits.CKP = 1;
       }

      if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) 
       {
           z = SSPBUF;
           while(!BF);
           PORTB = SSPBUF;
           SSPCONbits.CKP = 1;
           SSPM3 = 0;
       }
       else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
       {
           z = SSPBUF;
           BF = 0;
           SSPBUF = PORTB ;
           SSPCONbits.CKP = 1;
           while(SSPSTATbits.BF);
       }
       
       SSPIF = 0;
    }
}

void I2C_Slave_Init(short address)
{
    SSPSTAT = 0x80;
    SSPADD = address;
    SSPCON = 0x36;
    //SSPCON2 = 0x01;
    //TRISA3 = 1;
    //TRISA4 = 1;
    TRISA=1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}

void main()
{
    nRBPU = 0;
    TRISA = 0xFF;
    TRISB = 0x00;
    PORTB = 0x00;
    I2C_Slave_Init(0x30);
    while(1);
}

