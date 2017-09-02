

#include <htc.h>
//#define _XTAL_FREQ 4000000
// PIC12F508 Configuration Bit Settings
// CONFIG
//#pragma config OSC = ExtRC      // Oscillator Selection bits (external RC oscillator)
//#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config CP = OFF         // Code Protection bit (Code protection off)
#pragma config MCLRE = ON       // GP3/MCLR Pin Function Select bit (GP3/MCLR pin function is MCLR)
 
#include <stdio.h> 
#include <stdlib.h>
#include <xc.h>
#pragma config OSC = IntRC 
#pragma config WDT = OFF 
#pragma config CP = OFF 
#pragma config MCLRE = ON
#define _XTAL_FREQ 4000000






void main()
{
    OPTION = 0b00000000; //with out this gpio 2 will not run 
    TRISGPIO = 0b000000; //setting all of my pins to outputs (gpio3 is input only)
    
    
  while(1)
  { 

   GPIObits.GP0 = 1;
    __delay_ms(1000);
    
   GPIObits.GP0 = 0;   
    __delay_ms(1000);
   
   
  }
}