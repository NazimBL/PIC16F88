 */
 * Nazim BL
 * MPLAB X IDE
 */ 
 
 #include <p16f88.inc>
 
 __CONFIG _CONFIG1, _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _BOREN_ON & _LVP_ON & _CPD_OFF & _WRT_OFF & _CCPMX_RB0 & _CP_OFF
 __CONFIG _CONFIG2, _FCMEN_ON & _IESO_ON
    
 org 0 
 Main:
   ;select bank , trisb = bank 1 , place =86h
   bsf STATUS,RP0
   bcf STATUS,RP1   
     
   clrw
   movwf TRISB
   
    ;select bank , portb = bank 0 , place =06h
   bcf STATUS,RP0
   bcf STATUS,RP1
   
   Loop: 
   
    movlw B'00000000'
    movwf PORTB
    movlw B'00000010'
    movwf PORTB
   
   goto Loop
   end
