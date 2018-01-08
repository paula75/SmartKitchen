#include "nfc.h"

static nfc_iso14443a_t card;
static pn532_t pn532;

/*
==========================================================================
Name: nfc_init
Version: 1.0
Beschreibung: Initialisiert den PN532 NFC Reader
input:
output: ret : -1 = Error, 0 = OK
library: nfc.h
==========================================================================
*/
int nfc_init(void){
  int ret;

  //I2C oder SPI im Makefile einstellen
  #if defined(PN532_SUPPORT_I2C)
      ret = pn532_init_i2c(&pn532, &pn532_conf[0]);
  #elif defined(PN532_SUPPORT_SPI)
      ret = pn532_init_spi(&pn532, &pn532_conf[0]);
  #else
  #error None of PN532_SUPPORT_I2C and PN532_SUPPORT_SPI set!
  #endif

  if(ret != 0) return ret; /* if ret != 0 error*/

  ret = pn532_sam_configuration(&pn532, PN532_SAM_NORMAL, 1000);
  return ret;
}

/*
==========================================================================
Name: nfc_read_data
Version: 1.0
Beschreibung: Liest die ersten 16 bit Daten von einem Mifare-Tag ein
input: str_nfc_data :Speicher fuer Daten
output: ret : -1 = Error, 0 = OK
library: nfc.h
==========================================================================
*/
int nfc_read_data(char *str_nfc_data){
  int ret;

  ret = pn532_get_passive_iso14443a(&pn532, &card, 0x50);
  if (ret < 0) {
      //LOG_DEBUG("no card\n");
      //continue;
  }

  if (card.type == ISO14443A_MIFARE) {
      //Verifizierungsschluessel
      char key[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
      char data[32];

      /*Verifizierung ob richtig gelesen wurde*/
      ret = pn532_mifareclassic_authenticate(&pn532, &card,
                                             PN532_MIFARE_KEY_A, key, 3);
      if (ret != 0) {
          return 0;
      }

      /*Ersten 16 Daten bit lesen*/
      ret = pn532_mifareclassic_read(&pn532, data, &card, 0);
      if (ret == 0) {
          storebuff(data, 16, str_nfc_data);
          return 1;
        }
    }
    return 0;
}

/*
==========================================================================
Name: storebuff
Version: 1.0
Beschreibung: Speichert die NFC Daten in einen String
input: buff : NFC Daten
       len : laenge der Daten
output: store : NFC Daten als String
library: nfc.h
==========================================================================
*/
void storebuff(char *buff, unsigned len, char *store){
  strcpy(store, "");
  char temp[1];
    //Daten String aufbauen
    while (len) {
        len--;
        sprintf(temp, "%02x", *buff++);
        strcat(store, temp);
    }
}
