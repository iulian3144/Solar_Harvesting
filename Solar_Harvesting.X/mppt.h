#ifndef _MPPT_H_
#define _MPPT_H_

#define BUCK CCPR2L
#define BOOST CCPR1L

float read_Iout(void);

float read_Uout(void);

float read_Uin(void);

void write_Iout(float output_amperage);

void write_Uout(float output_voltage);

void write_Uin(float input_voltage);

void pwm_init(float input_voltage, int *boost_pwm);

#endif // _MPPT_H
