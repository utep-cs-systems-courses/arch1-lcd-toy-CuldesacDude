#ifndef wakedemo_included
#define wakedemo_included
#include "lcdutils.h"
#include "lcddraw.h"
#define LED_GREEN BIT6

extern u_char a, b ,L_R, nextL_R, U_D ,nextU_D;

void wdt_c_handler();

void StartGame();

#endif //included
