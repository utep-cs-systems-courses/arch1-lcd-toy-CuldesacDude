#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char state = 0;

void countToThree(){
  //this controlls the leds, with the first switch of the greeen board
  
  switch(state){
  case 0:
    buzzer_set_period(1000); red_on = 0; green_on = 0;
    state = 1;
    break;
    
  case 1:
    buzzer_set_period(800); red_on = 1; green_on = 0;
    state = 2;
    break;

  case 2:
    buzzer_set_period(600); red_on = 0; green_on = 1;
    state = 3;
    break;

  case 3:
    buzzer_set_period(400); red_on = 1; green_on = 1;
    state = 0;
    break;

  }
  led_changed = 1; //we update the lights after each break
  led_update();
  
}

static char secState = 0;
static int secPeriod = 0;
void secBttn(){
  switch(secState){
  case 0:secPeriod = 704; secState = 1; red_on =0; green_on=1;
    break;
  case 1:secPeriod = 0; secState = 2;
    break;  
  case 2:secPeriod = 704;secState = 3;red_on =1; green_on=0;
    break;
  case 3:secPeriod = 0; secState = 4;
    break;
  case 4:secPeriod = 704; secState = 5;red_on =0; green_on=1;
    break;
  case 5:secPeriod = 0; secState = 6;
    break;
  case 6:secPeriod = 1674; secState = 7;red_on =1; green_on=0;
    break;
  case 7:secPeriod = 0; secState = 8;
    break;
  case 8:secPeriod = 1184; secState = 9;red_on =0; green_on=1;
    break;
  case 9:secPeriod = 0; secState = 10;
    break;
  case 10:secPeriod = 704; secState = 11; red_on = 1; green_on=0;
    break;
  case 11:secPeriod = 0; secState = 0;
    break;
  }
  buzzer_set_period(secPeriod);
  led_changed =1;
  led_update();
}

void reset(){
  buzzer_set_period(0);
  count = 0;
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}
