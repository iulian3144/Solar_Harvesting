/*
 * File:   config.h
 * Author: Silviu Chirica
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <xc.h> // include processor files - each processor file is guarded.
#include "lcd_i2c.h"

void config(void);

void pwm_config(void);

void adc_config(void);

void init_io_display(void);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C
    // linkage so the functions can be used by the c code.

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CONFIG_H_ */
