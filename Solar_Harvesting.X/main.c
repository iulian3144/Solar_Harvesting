#include "main.h"
#define  buck  CCPR2L
#define  boost CCPR1L



void main(void)
{
   
    config();
    pwm_config();
    adc_config();
    init_io_display();
    Lcd_Clear(); 
    read_Uin();
    pwm_init(Uin);
    float Uin,Power,Power_new;
    int port,c,d,buck_pwm,boost_pwm;
    buck_pwm=50;

    
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

        Power=Uout*Iout;

        if(Uin>12)//functia de MPPT pentru regimul de buck
        {
            boost=0;
            buck=buck_pwm++;
            read_Iout();
            read_Uout();
            Power_new=Uout*Iout;
            if(Power_new>Power)
            {
                 Power=Power_new;
            }
            else
            {
                buck=buck_pwm-2;
                read_Iout();
                read_Uout();
                Power_new=Uout*Iout;
                if(Power_new>Power)
                {
                    Power=Power_new;
                }
            }
        }
        
        if(Uin<=12)//functia de MPPT pentru regimul de boost
        {
            buck=128;//80%
            boost=boost_pwm++;
            read_Iout();
            read_Uout();
            Power_new=Uout*Iout;
            if(Power_new>Power)
            {
                 Power=Power_new;
            }
            else
            {
                boost=boost_pwm-2;
                read_Iout();
                read_Uout();
                Power_new=Uout*Iout;
                if(Power_new>Power)
                {
                Power=Power_new;
                }   
            }
        }
    }
}