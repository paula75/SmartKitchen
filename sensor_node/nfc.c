#include "nfc.h"

static nfc_iso14443a_t card;
static pn532_t pn532;

int nfc_init(void){
  int ret;

  #if defined(PN532_SUPPORT_I2C)
      ret = pn532_init_i2c(&pn532, &pn532_conf[0]);
  #elif defined(PN532_SUPPORT_SPI)
      ret = pn532_init_spi(&pn532, &pn532_conf[0]);
  #else
  #error None of PN532_SUPPORT_I2C and PN532_SUPPORT_SPI set!
  #endif

  if(ret != 0) return ret; /* if ret != 0 error*/

  //uint32_t fwver;
  //pn532_fw_version(&pn532, &fwver);
  //OG_INFO("ver %d.%d\n", (unsigned)PN532_FW_VERSION(fwver), (unsigned)PN532_FW_REVISION(fwver));
  ret = pn532_sam_configuration(&pn532, PN532_SAM_NORMAL, 1000);
  //LOG_INFO("set sam %d\n", ret);
  return ret;
}

int nfc_read_data(char *str_nfc_data){
  int ret;

  ret = pn532_get_passive_iso14443a(&pn532, &card, 0x50);
  if (ret < 0) {
      //LOG_DEBUG("no card\n");
      //continue;
  }

  if (card.type == ISO14443A_MIFARE) {
      char key[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
      char data[32];

      /*Verfiy sector 0 block 4*/
      ret = pn532_mifareclassic_authenticate(&pn532, &card,
                                             PN532_MIFARE_KEY_A, key, 3);
      if (ret != 0) {
          //LOG_ERROR("auth\n");
          return 0;
      }

      /*Read data from sector 0 block 0*/
      ret = pn532_mifareclassic_read(&pn532, data, &card, 0);
      if (ret == 0) {
          //printbuff(data, 16);
          //char str_nfc_data[16];
          storebuff(data, 16, str_nfc_data);
          return 1;
        }
    }
    return 0;
}

void storebuff(char *buff, unsigned len, char *store){
  strcpy(store, "");
  char temp[1];
    while (len) {
        len--;
        sprintf(temp, "%02x", *buff++);
        strcat(store, temp);
    }
}
