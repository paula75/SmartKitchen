#ifndef FSR_H
#define FSR_H

#include "periph/adc.h"

#define RES             ADC_RES_10BIT

int fsr_init_adc(void);

int fsr_read_adc(int pin_number);

int fsr_read(int pin_number);

long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif /* FSR_H */
