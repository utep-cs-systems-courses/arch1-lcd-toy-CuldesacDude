#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"
#include "Game.h"

char SW1down, SW2down, SW3down, SW4down, mSwi, switch_state_changed;

char switch_update_interrupt_sense(){

  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}

void switch_init()/* setup switch */{

  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  switch_update_interrupt_sense();

  //led_update();

}

/* I had put reset and countToThree here as i just want them to be single button presses

   although reset must be held for the buzzer to stop. bttnState is just the state of the buttons.*/

void switch_interrupt_handler(){

  char p2val = switch_update_interrupt_sense();

  SW1down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  SW2down = (p2val & SW2) ? 0 : 1;
  SW3down = (p2val & SW3) ? 0 : 1;
  SW4down = (p2val & SW4) ? 0 : 1;

  if(SW1down){

    sound();
    
  }
  
}
