#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "wakedemo.h"

//#include "stateMachines.h"

static char state = 0;

void countToThree(){
  //this controlls the leds, with the first switch of the greeen board
  
  switch(state){
  case 0:
    h1 = 50;
    state = 1;
    break;
    
  case 1:
    h1=10;
    state = 0;
    break;
  }
}

static char secState = 0;
static int secPeriod = 0;
void secBttn(){
  switch(secState){
  case 0:
    break;
  }
}
