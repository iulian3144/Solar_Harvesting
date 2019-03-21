/*
 * File:   mppt.c
 * Author: Silviu Chirica
 *
 * Created on March 12, 2019, 12:45 PM
 */

#include "bit_config.h"
#include "config.h"
#include <pic18f46k22.h>
#include <stdio.h>
#include <xc.h>

/*
 * Citeste valoarea curentului de iesire.
 */
float read_Iout(void) {
    float adcA_resolution = ADRESH;
    ADCON0 = 0b00001011; // RA2
    __delay_ms(10);
    ADCON0bits.GO = 1;
    __delay_ms(100);
    tens_A = adcA_resolution * 0.0181372549019608; // should be optimized

    return tens_A;
}

/*
 * Citeste valoarea tensiunii de iesire.
 */
float read_Uout(void) {
    float voltage = 0;
    ADCON0 = 0b00000111; // RA1
    __delay_ms(10);
    ADCON0bits.GO = 1;
    __delay_ms(100);
    rez_adc_U = ADRESH;
    voltage = rez_adc_U * 0.01953125;
    output_voltage = voltage / 0.25;

    return output_voltage;
}

/*
 * Citeste valoarea tensiunii de intrare.
 * @return valoarea tensiunii de intrare
 */
float read_Uin(void) {
    float voltage;
    float input_voltage = 0;
    ADCON0 = 0b00001111; // RA3
    __delay_ms(10);
    ADCON0bits.GO = 1;
    __delay_ms(100);
    rez_adc_U = ADRESH;
    voltage = rez_adc_U * 0.01953125;
    input_voltage = voltage * 5;    // avoid using division
                                    // multiplication is easier for processors

    return input_voltage;
}

/*
 * Afiseaza pe display valoarea curentului de iesire.
 * @param output_amperage valoarea curentului de iesire
 */
void write_Iout(float output_amperage) {
    char amperage_text[9] = {0}; // 8 chars + end of string
    Lcd_Set_Cursor(2, 1);
    snprintf(amperage_text, 16, "Iout: %.2fA", output_amperage);
    Lcd_Write_String(amperage_text);
}

/*
 * Afiseaza pe display valoarea tensiunii de iesire.
 * 1234567812345678
 * U=12.34
 * @param output_voltage valoare tensiunii de iesire
 */
void write_Uout(float output_voltage) {
    char voltage_text[9] = {0};
    Lcd_Set_Cursor(1, 1);
    snprintf(voltage_text, 8, "U=%.2f", output_voltage);
    Lcd_Write_String(voltage_text);
}

/*
 * Afiseaza pe display valoarea tensiunii de intrare.
 * 1234567812345678
 *         Ui=12.34
 * @param input_voltage valoare tensiunii de intrare
 */
void write_Uin(float input_voltage) {
    char voltage_text[9] = {0}; // 8 chars + end of string
    Lcd_Set_Cursor(1, 9);
    snprintf(voltage_text, 8, "Ui=%.2f", input_voltage);
    Lcd_Write_String(voltage_text);
}

/*
 * Initializeaza PWM.
 * @param input_voltage valoare tensiunii de intrare
 * @param boost_pwm
 */
void pwm_init(float input_voltage, int *boost_pwm) {
    if (input_voltage > 12) {
        *boost_pwm = 0;
        buck = *boost_pwm;
    }
}
