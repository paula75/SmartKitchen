#include "fsr.h"

/*
================================================================
Name: fsr_init_adc
Version: 1.0
Beschreibung: Initialisierung des ADC
input:
output:
Libaray:fsr.h
================================================================
*/

int fsr_init_adc(void){
  // Initialisierung aller ADC-Lines
  for (int i = 0; i < ADC_NUMOF; i++) {
      if (adc_init(ADC_LINE(i)) < 0) {
          return 1;
      }
  }
  return 0;
}

/*
================================================================
Name: fsr_read_adc
Version: 1.0
Beschreibung: Einlesen eines Analogwertes, convertiert in einen
digitalen Wert
input: int pin_number (Pin Nummer des Input)
output: sample (ADC des Analogwertes) , im Fehlerfall -1
Libaray:fsr.h
================================================================
*/

int fsr_read_adc(int pin_number){
  // Einlesen des ADC
  int sample = adc_sample(ADC_LINE(pin_number), RES);
  if (sample < 0) {
    // Fehlerfall
      return -1;
  } else {
    return sample;
  }
}


/*
================================================================
Name: fsr_read
Version: 1.0
Beschreibung: Einlesen eines Analogwertes, Umrechnung von einem
Druckwert in das entsprechende Gewicht bei einem fsr400
input: int pin_number (Pin Nummer des Input)
output: int fsrForce (Gewicht)
Libaray:fsr.h
================================================================
*/

int fsr_read(int pin_number){
  long fsrVoltage;
  unsigned long fsrResistance;
  unsigned long fsrConductance;
  long fsrForce;

  // Einlesen des ADC
  int sample = fsr_read_adc(pin_number);
  // ADC an 5V anpassen
  fsrVoltage = map(sample, 0, 1023, 0, 5000);

  // Berechnung des Gewichts
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

/*
================================================================
Name: map
Version: 1.0
Beschreibung: Matcht den Wert vom aktuellen Wertebereich in die
gleiche Wertigkeit im gewünschten Wertebereich
input: aktueller Wert, Aktueller Wertebereich, gewünschter
Wertebereich
output: angepasster Wert
Libaray:fsr.h
================================================================
*/
long map(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
