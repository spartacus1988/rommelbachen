#include <htc.h>
#include <stdio.h> 
#include <stdlib.h>
#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled

#define _XTAL_FREQ 4000000


 void SetPwmValue(unsigned int pwm)
    {
       GPIObits.GP5 = 1;
        __delay_ms(pwm);
    
        GPIObits.GP5 = 0;   
        __delay_ms(10);
    }
 

void main()
{
   
	GPIO 	= 0x00;
    TRISIO 	= 0x1F;			//	Making pin GP5 as output and all others input
    CMCON	= 0x07;			// Disabling comparator
    IOC 	= 0x00;			// Disabling Interrupt on change on all pins
    OPTION_REG = 0x80;      // Disable pull-up resistors, Interpt on falling edge on GP2/INT pin
    
    
    unsigned int pwm =0;
    
    while(1)
    { 
        
        
       // GPIObits.GP5 = 1;
       //__delay_ms(10);
    
       // GPIObits.GP5 = 0;   
       // __delay_ms(100);
   
        
        SetPwmValue(500);
        
                
                
   
    }
}