#ifndef NFC_H
#define NFC_H

#include "pn532.h"
#include "pn532_params.h"
#include <string.h>


int nfc_init(void);

int nfc_read_data(char *str_nfc_data);

void storebuff(char *buff, unsigned len, char *store);


#endif /* NFC_H */
