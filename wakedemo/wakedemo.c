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

u_char U_D = 10;
u_char nextU_D = 10;

u_char L_R = 10;
u_char nextL_R = 10;

signed char Speed = 2; 

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
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    u_int switches = p2sw_read(), i;
    char str[5];
    
    for(i=0;i<4;i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;

      if(str[0]=='0'){
	//drawString5x7(50,50,"H",COLOR_GREEN, COLOR_BLUE);
	nextU_D += Speed;

      }
      if(str[1]=='1'){
	nextU_D -= Speed;
      }
      if(str[2]=='2'){
	nextL_R -=Speed;	
      }
      if(str[3]=='3'){
        nextL_R +=Speed;	
      }
     
    }
    str[4] = 0;
    drawString5x7(20,20,str,COLOR_WHITE, COLOR_BLACK);

    if (redrawScreen) {
	redrawScreen = 0;

	fillRectangle(L_R,U_D,10,10, COLOR_BLACK);
	fillRectangle(nextL_R,nextU_D,10,10, COLOR_RED);
	L_R = nextL_R;	      
	U_D = nextU_D;
	
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



