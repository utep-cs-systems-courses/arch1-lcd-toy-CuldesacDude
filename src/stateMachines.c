#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char state = 0;

void sound(){
  
  switch(state){
  case 0:
    buzzer_set_period(700);
    state = 1;
    break;
    
  case 1:
    buzzer_set_period(0);
    state = 0;
    break;

  }
  led_changed = 1; //we update the lights after each break
  led_update();
  
}

void FUCK (){
  buzzer_set_period(1000);
}
