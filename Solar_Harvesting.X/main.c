/*
 * File:   main.c
 * Author: Silviu Chirica
 */

#include "mppt.h"

void main(void) {
    int boost_pwm = 0;
    int buck_pwm = 0;
    float output_voltage = 0.0;
    float input_voltage = 0.0;
    float output_amperage = 0.0;
    float Power = 0;
    float Power_new = 0;

    config();
    pwm_config();
    adc_config();
    init_io_display();
    Lcd_Clear();
    input_voltage = read_Uin();
    pwm_init(input_voltage, &boost_pwm);
    int port, c, d;
    buck_pwm = 50;

    while (1) {
        if (port == 0) {
            output_amperage = read_Uout();
            write_Uout(output_voltage);
            port = 1;
            __delay_ms(100);
            ADRESH = 0X00;
            __delay_ms(100);
        }

        if (port == 1) {
            output_amperage = read_Iout();
            write_Iout(output_amperage);
            port = 2;
            __delay_ms(100);
            ADRESH = 0X00;
            __delay_ms(100);
        }

        if (port == 2) {
            input_voltage = read_Uin();
            port = 0;
            __delay_ms(100);
            ADRESH = 0X00;
            __delay_ms(100);
        }

        Power = output_voltage * output_amperage;

        if (input_voltage > 12) // functia de MPPT pentru regimul de buck
        {
            BOOST = 0;
            BUCK = buck_pwm++;
            output_amperage = read_Iout();
            output_voltage = read_Uout();
            Power_new = output_voltage * output_amperage;
            if (Power_new > Power) {
                Power = Power_new;
            } else {
                BUCK = buck_pwm - 2;
                output_amperage = read_Iout();
                output_voltage = read_Uout();
                Power_new = output_voltage * output_amperage;
                if (Power_new > Power) {
                    Power = Power_new;
                }
            }
        }

        if (input_voltage <= 12) // functia de MPPT pentru regimul de boost
        {
            BUCK = 128; // 80%
            BOOST = boost_pwm++;
            output_amperage = read_Iout();
            output_voltage = read_Uout();
            Power_new = output_voltage * output_amperage;
            if (Power_new > Power) {
                Power = Power_new;
            } else {
                BOOST = boost_pwm - 2;
                output_amperage = read_Iout();
                output_voltage = read_Uout();
                Power_new = output_voltage * output_amperage;
                if (Power_new > Power) {
                    Power = Power_new;
                }
            }
        }
    }
}
