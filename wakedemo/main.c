#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "wakedemo.h"


int main(void) {
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  switch_init();
  StartGame();
  
  or_sr(0x18);/* CPU off, GIE on */

}
