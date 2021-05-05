#ifndef stateMachine_included
#define stateMachine_included
#include "led.h"
#include "buzzer.h"
#include "shape.h"
#include "switches.h"
#include "lcddraw.h"
#include "switches.h"
#include "lcdutils.h"

char count;
char dimState;
char sirenState;

void countToThree();
void dim75();
short convertperiod(short period);
short asPeriod(short pd);
void siren();
void sirenShapeAdvance();
void sirenStateAdvance();
void reset();

#endif // included
