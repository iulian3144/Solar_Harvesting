#include "main.h"


void main(void)
{
    
    config();
    pwm_config();
    adc_config();
    init_io_display();
    Lcd_Clear();
    int port,c;
    c=50;
    while(1)
    {
        if(port==0)
        {
            read_Uout();
            port=1;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
         }
    
        if(port==1)
        {   
            read_Iout();
            port=2;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
        }
        
        if(port==2)
        {   
            read_Uin();
            port=0;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
        }

        c=100;
       
        CCPR2L=c;
   
        
        
//Power=Uout*Iout;

    }
}