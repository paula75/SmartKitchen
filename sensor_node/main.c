#include "board.h"

#include "xtimer.h"

#include <string.h>


#include <stdlib.h>
#include <stdio.h>

#include "thread.h"

#include "fsr.h"
#include "coap_put.h"
#include "nfc.h"


#define DELAY_SHORT     (1000LU * US_PER_MS) /* 100 ms */
#define DELAY           (10000LU * US_PER_MS) /* 10000 ms */

#define LOG_LEVEL LOG_INFO
#include "log.h"

int main(void)
{

    xtimer_ticks32_t last = xtimer_now();

    fsr_init_adc();
    nfc_init();

    xtimer_usleep(100000); //sleep 5 seconds
    while (1) {
      xtimer_periodic_wakeup(&last, DELAY_SHORT);
      char str_nfc_data[16];

      if(nfc_read_data(str_nfc_data)) {
          if(strcmp(str_nfc_data,"") == 0){
              LOG_INFO("DATA SEND: Kaese\n");
              put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", "Kaese");
          }else if(strcmp(str_nfc_data,"") == 0) {
              LOG_INFO("DATA SEND: Wurst\n");
              put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", "Wurst");
          }else{
            LOG_INFO("DATA SEND: %s\n", str_nfc_data);
            put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", str_nfc_data);
          }

          for(int e = 0; e < 4; e++) {
            xtimer_periodic_wakeup(&last, DELAY_SHORT);
            int sample = fsr_read_adc(0);
            char temp_wert[10];
            sprintf(temp_wert, "%d", sample);
            LOG_INFO("DATA SEND: %s\n",temp_wert);
            put("fe80::1ac0:ffee:1ac0:ffee", "/sensor", temp_wert);
          }

      }
    }
    return 0;
}
