#ifndef wakedemo_included
#define wakedemo_included
#include "lcdutils.h"
#include "lcddraw.h"
#define LED_GREEN BIT6

extern u_char h1;

void wdt_c_handler();

void StartGame();

#endif //included
