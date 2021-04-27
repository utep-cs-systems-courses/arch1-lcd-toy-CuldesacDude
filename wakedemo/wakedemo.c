#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

u_char helloCol = 10;
u_char nextHelloCol = 10;
u_char h1 = 10;

signed char helloVelocity = 1; 

void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;

  secCount ++;
  dsecCount ++;

  
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_RED) ? COLOR_WHITE : COLOR_RED;
    redrawScreen = 1;
  }
  if(dsecCount==25){
    dsecCount = 0;
    nextHelloCol += helloVelocity;
    if(nextHelloCol > 90 || nextHelloCol <= 0){
      helloVelocity = -helloVelocity;
      nextHelloCol += helloVelocity;
    }
    redrawScreen = 1;
  }
}

void StartGame()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */


  //static u_char h1 = helloCol; 
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    u_int switches = p2sw_read(), i;
    char str[5];

    for(i=0;i<4;i++){
      str[i] = (switches & (1<<i)) ? '10' : '20'+i;
      h1 = str[i];
    }
    str[4] = 0;
    drawString5x7(20,20,str,COLOR_GREEN, COLOR_BLUE);

    if (redrawScreen) {
	redrawScreen = 0;

	fillRectangle(10,helloCol,h1,10, COLOR_BLACK);
	fillRectangle(10,nextHelloCol,h1,10, COLOR_RED);
		      
	helloCol = nextHelloCol;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



