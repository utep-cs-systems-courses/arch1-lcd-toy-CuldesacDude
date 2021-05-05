#include <msp430.h>
#include "libTimer.h"
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"

short redrawScreen = 1;
/*i left the handler as is, however I tried making it so if button 2 was pressed
  it will increment dimState but that failed*/
void wdt_c_handler()
{
  static int blinkCount = 0;
  if(++blinkCount == 250){
    blinkCount = 0;
    redrawScreen = 1;
  }
}
void main(void)
{
  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;

  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  buzzer_init();
  lcd_init();
  switch_init();
  or_sr(0x8);/*GIE on allows interrupts*/
  clearScreen(COLOR_BLACK);

  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      switch(bttnState){
      case 1:
	countToThree();
	break;
      case 2:
	dim75();
	break;
      case 3:
	reset();
	break;
      case 4:
	sirenStateAdvance();
	break;
      }
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);/*CPU off*/
    P1OUT |= LED_GREEN;
  }
}
