#include "fsr.h"

int fsr_init_adc(void){
  /* initialize all available ADC lines */
  for (int i = 0; i < ADC_NUMOF; i++) {
      if (adc_init(ADC_LINE(i)) < 0) {
          return 1;
      }
  }
  return 0;
}

int fsr_read_adc(int pin_number){
  int sample = adc_sample(ADC_LINE(pin_number), RES);
  if (sample < 0) {
      return -1;
  } else {
    return sample;
  }
}

int fsr_read(int pin_number){
  long fsrVoltage;
  unsigned long fsrResistance;
  unsigned long fsrConductance;
  long fsrForce;

  int sample = fsr_read_adc(pin_number);
  fsrVoltage = map(sample, 0, 1023, 0, 5000);

  fsrResistance = 5000 - fsrVoltage;
  fsrResistance *= 10000;
  fsrResistance /= fsrVoltage;

  fsrConductance = 1000000;
  fsrConductance /= fsrResistance;

  if (fsrConductance <= 1000) {
    fsrForce = (fsrConductance / 80.0) * 100;
    return (int)fsrForce;
  } else {
    fsrForce = fsrConductance - 1000;
    fsrForce = (fsrForce / 30.0) * 100;
    return (int)fsrForce;
  }

}

long map(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
