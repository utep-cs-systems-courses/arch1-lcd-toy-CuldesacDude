#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

void __interrupt_vec(WDT_VECTOR) WDT(){/* 250 interrupts/sec */

  static char buzzCount =0;

  if(++buzzCount == 65 && mSwi == 1){
    secBttn();
    buzzCount=0;
  }
  else if(mSwi == 2){
    buzzer_set_period(0);
    buzzCount=0;
  }
  
}
