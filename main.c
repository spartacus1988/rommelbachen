#include <htc.h>
#include <stdio.h> 
#include <stdlib.h>
#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled

#define _XTAL_FREQ 4000000


unsigned int ADC_get_state()
{
    ADRESH = 0x00;
    ADRESL = 0x00;
    ADCON0 = 0x8D;      //AN3
    __delay_us(25);
    GO_nDONE = 1;
    while(GO_nDONE);
    return (ADRESH<<8) + ADRESL;
}
unsigned int ADC_get_PWM()
{
    ADRESH = 0x00;
    ADRESL = 0x00;
    ADCON0 = 0x85;      //AN1
    __delay_us(25);
    GO_nDONE = 1;
    while(GO_nDONE);
    return (ADRESH<<8) + ADRESL;
}


void adc_init()
{
	ANSEL 	= 0x5A;			// ADC freq = FOSC/16(ANSEL<6:4>); GP1(AN1) and GP4(AN3) set as analog input pin(for ADC), rest all digital pins 
    ADCON0 	= 0x8D;			// Right justified output, ADC on, ADC channel ANS0/GP0 , GO/nDONE = 0
                            //The CHS1:CHS0 bits (ADCON0<3:2>) control which channel is connected to the sample and hold circuit
                            //The VCFG (ADCON0<6>) is not set to 1, then VDD is ref(otherwise Vref is reference)
                            //The ADFM bit (ADCON0<7>) controls the output format. 1 is right shifted 10 bit ADC is return (ADRESH<<8) + ADRESL;
                            //The ADON bit (ADCON0<0>)=1 it means A/D converter module is operating now (on/off ADC conversation)
}


 void SetPwmValue(unsigned int pwm_i)
    {
       pwm_i = pwm_i / 100;
       
       GPIObits.GP5 = 1;
        __delay_ms(pwm_i);
    
        GPIObits.GP5 = 0;   
        __delay_ms(10);
    }
 

void main()
{
    //__delay_ms(300);
    
	GPIO 	= 0x00;
    TRISIO 	= 0x1E;			//	Making pin GP0 and GP5 as output and all others input
    CMCON	= 0x07;			// Disabling comparator
    IOC 	= 0x00;			// Disabling Interrupt on change on all pins
    OPTION_REG = 0x80;      // Disable pull-up resistors, Interpt on falling edge on GP2/INT pin
    
    
    unsigned int pwm;
    unsigned int state;
    unsigned int state_switch;
    unsigned int old_state;
    unsigned int state_counter = 150;
    unsigned int pwm_counter = 150;
    unsigned int GPIOO;
    
    
     adc_init();
    // __delay_ms(300);
    
    while(1)
    {  
        
        
        state_counter--;
        //GPIObits.GP0 = GPIOO;      //power on potentiomenrt
        GPIObits.GP0 = 1;            //power on potentiomenrt
   
        if(state_counter == 0)
        {
            //state_counter = 250;
            state = ADC_get_state();
            pwm_counter = ADC_get_PWM();
            pwm_counter = pwm_counter / 10;
        }
        
        
        
             
        if ((state > 640)&&(old_state<100))
        {   
            GPIOO=~GPIOO;           
        }
        
        
        if(GPIOO)
        {      
            //GPIObits.GP0 = GPIOO;
            //GPIObits.GP5 = GPIOO;
           // SetPwmValue(0);
        }
        else
        {
            //GPIObits.GP0 = GPIOO;
            //GPIObits.GP5 = GPIOO;
            //SetPwmValue(0);
        }
        
  
        
        
        //GPIObits.GP0 = 1;      //power on potentiomenrt
   
        
        
        
        
        if(!GPIOO)//(state_switch) 
        {
            pwm_counter--;
            if(pwm_counter==0)
            {
               GPIObits.GP5 = 0; 
            }
            else 
            {
              GPIObits.GP5 = 1;   
            }   
            
            //pwm = ADC_get_PWM();
            //SetPwmValue(500);
            //GPIObits.GP5 = 1;
        }
        else
        {
            
            //GPIObits.GP5 = 0;
            //__delay_ms(3000);
        }
        
        old_state =  state;  
        
    }
}