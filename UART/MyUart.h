
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void UART_init(long baudrate){
   
    //low speed / high speed dosent work good still dk why
    BRGH=1;    
                                      //Writing SPBRG Register
    //115200
    if(baudrate==9600)SPBRG=51;
    else if(baudrate==57600)SPBRG=8;
    else if(baudrate==115200)SPBRG=4;
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port 
    RCIE=1;
    CREN = 1;                                     //Enables Continuous Reception
    TXEN = 1;                                     //Enables Transmission
                                           
}
void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
}
char UART_TX_Empty()
{
  return TRMT;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
      UART_Write(text[i]);
}

//return char when rcif is 1
char UART_Read()
{  
  while(!RCIF);
  return RCREG;
  // char c=RCREG;
  //UART_Write(c);
  //UART_Write('\n');
}
void UART_Read_Text(char *Output,int length)
{
  for(int i=0;i<length;i++){ 
   Output[i]=UART_Read();  
  }
}
void UART_ReadSentence(char *output,int index){
    output[index]=UART_Read();
}
void UART_ReadChar(){
     if(RCIF){
            
            UART_Write_Text("data available \n");

            char c=UART_Read();
            UART_Write(c);
            UART_Write('\n') ;           
            //UART_CorrectError();
            //c='0';
                              
        }else {
           
            UART_Write_Text("nothin to read bruh \n");
        }
}

 char UART_available()
{     
     if(RCIF)return '1';
     else return '0'; 
}
void UART_CorrectError(){
    while(OERR){
              //error managment
        char temp;
              UART_Write_Text("Clearing Buffer... \n");
              temp=RCREG;
              temp=RCREG;
              temp=RCREG;
              CREN=0;
              CREN=1;
          }    
}
#endif	/* XC_HEADER_TEMPLATE_H */

