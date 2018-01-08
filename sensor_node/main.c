#include "board.h"

#include "xtimer.h"

#include <string.h>


#include <stdlib.h>
#include <stdio.h>

#include "thread.h"

#include "fsr.h"
#include "coap_put.h"
#include "nfc.h"

#include "thread.h"
//#include "msg.h"


#define DELAY_SHORT     (2500LU * US_PER_MS) /* 250 ms */
#define DELAY           (10000LU * US_PER_MS) /* 10000 ms */

char stack[THREAD_STACKSIZE_MAIN];

#define LOG_LEVEL LOG_INFO
#include "log.h"

/*
==========================================================================
Name: measure_pressure_thread
Version: 1.0
Beschreibung: Liest einen Analogwert ein, wandelt ihn in einen Gewichtswert um
und sendet ihn der http put
input:
output:
library: fsr.h, coap_put.h
==========================================================================
*/
void *measure_pressure_thread(void *arg) {
    (void) arg;
    while(1) {
      msg_t msg
      xtimer_ticks32_t last = xtimer_now();
      if(msg_receive(&msg)) {
        int sample[4];
        double force[4];
        //Vier Analogwerte in Gewichtswerte umwandeln
        for(int e = 0; e < 4; e++) {
            xtimer_periodic_wakeup(&last, DELAY_SHORT);
            sample[e] = fsr_read_adc(0);
            force[e] = (sample[e] * 2.2287) - 474.21;
        }
        //Alle Werte in einen String umwandeln und per http put senden
        char str_force[10];
        sprintf(str_force, "%d, %d, %d, %d", (int)force[0], (int)force[1],
        (int)force[2], (int)force[3]);
        LOG_INFO("DATA SEND: %s\n", str_force);
        put("fe80::1ac0:ffee:1ac0:ffee", "/sensor", str_force);
      }
    }
    return NULL;

}

/*
==========================================================================
Name: main
Version: 1.0
Beschreibung: Liest periodisch einen NFC-Tag ein und sendet ihn per http put,
startet den Thread measure_pressure_thread
input:
output:
library: nfc.h, coap_put.h, thread.h
==========================================================================
*/
int main(void)
{

    xtimer_ticks32_t last = xtimer_now();

    //Alles Initialisieren
    fsr_init_adc();
    nfc_init();

    //Einen Thread fuer die Gewichtsmessung erstellen
    int pid = thread_create(stack, sizeof(stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    measure_pressure_thread,
                    NULL, "measure_pressure");
    pid = pid + 1 - 1;

    msg_t msg;
    //kernel_pid_t main_id = thread_getpid();

    xtimer_usleep(100000); //sleep 5 seconds
    LOG_INFO("READY!\n");
    while (1) {
      xtimer_periodic_wakeup(&last, DELAY_SHORT);
      char str_nfc_data[16];

      //NFC-Tag lesen und per http put senden
      if(nfc_read_data(str_nfc_data)) {
          if(strcmp(str_nfc_data, "1e20fd0ccf0804000168a828b0aea51d") == 0){
              LOG_INFO("DATA SEND: Kaese\n");
              put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", "Kaese");
          }else if(strcmp(str_nfc_data, "d554362a9d080400018a84dcced4d71d") == 0) {
              LOG_INFO("DATA SEND: Wurst\n");
              put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", "Wurst");
          }else{
            LOG_INFO("DATA SEND: %s\n", str_nfc_data);
            put("fe80::1ac0:ffee:1ac0:ffee", "/nfc", str_nfc_data);
          }
          msg_send(&msg, pid);
      }
    }

    return 0;
}
