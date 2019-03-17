#include "main.h"



void main(void)
{
    
    config();
    pwm_config();
    adc_config();
    init_io_display();
    Lcd_Clear();
    float Uin;
    int port,c,d;
    read_Uin();
    pwm_init(Uin);

    
    while(1)
    {
        if(port==0)
        {
            read_Uout();
            write_Uout();
            port=1;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
         }
    
        if(port==1)
        {   
            read_Iout();
            write_Iout();
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
   
//Power=Uout*Iout;

    }
}