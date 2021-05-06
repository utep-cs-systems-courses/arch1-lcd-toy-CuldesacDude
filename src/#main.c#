#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "Game.h"

int main(void) {
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  led_init();
  buzzer_init();
  buzzer_set_period(0);//buzzer reset
  switch_init();
  StartGame();
  
  or_sr(0x18);/* CPU off, GIE on */

}
