#include <msp430.h>
#include "switches.h"

//for the switches on green board

void __interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {

    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */

    switch_interrupt_handler();/* single handler for all switches */

  }
}
