// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON
//LVP SHOULD BE DISABLED PICKIT3 Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = ALL        // Flash Program Memory Write Enable bits (0000h to 0FFFh write-protected)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF       // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

#include <xc.h>
char msg='r',transmit='w';

void initialize_i2c(){
	
    // set SDA and SCL to input    
TRISB4=1;
TRISB1=1;
    //set all state register values to zero ( initial value to avoid overflow and colision errors)
    SSPSTAT=0x00;
    /* configuration register :( from msb to lsb )
     * 0011 0110 = 0x36
     Wcol=0 colision bit
     sspov=0 overflow 
     sspen=1 enable ssp
     ckp=1 clock
     sspm = ssp mode = 6 = 0110
    */
     SSPCON=0x36;
    //set our adress , try to change it if this one doesn't work  
    //16
   SSPADD=0x17;
       //interupts ignor for now
   SSPIE=1;
   GIE = 1;
   PEIE = 1;
}   
  
void read(){

    if(SSPIF==1){
        CKP=0;
        if(SSPOV || WCOL){
   
            msg=SSPBUF;
            WCOL = 0;
            SSPOV=0;
             CKP= 1;
        }
           
       if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            
           //thanks budy
         
            while(!BF);
           msg=SSPBUF; 
           SSPOV=0;
               
       }       
        else if(SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
           
          while(!BF);
          while(PORTB & 0x02);
          msg=SSPBUF; 
          SSPOV=0;
       
          CKP = 1;
          SSPM3 = 0;
        }        
        SSPIF = 0;
    
}
}
void send(){

    if(SSPIF==1){
       
        CKP=0;
        if(SSPOV || WCOL){

            msg=SSPBUF;           
            WCOL = 0;
            SSPOV=0;
             CKP= 1;
        }
         if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
            
            CKP=0; 
           SSPBUF=transmit;
           SSPOV=0;
           CKP = 1;      
       } 
         if(SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
             while(!BF);
             while(PORTB & 0x02);
			 SSPBUF=transmit;
             SSPOV=0;
             CKP = 1;
              
           while(BF);
		}
    
     SSPIF = 0;
    }
}

void main() {
    
 initialize_i2c();
  
  while(1) {
	  
    //read();
      send();           
  }
  
}
