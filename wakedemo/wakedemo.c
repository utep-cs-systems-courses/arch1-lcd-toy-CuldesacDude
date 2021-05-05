#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>
#include <stdio.h>
#include "stateMachines.h"
#include <stdlib.h>
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
//direction of red cube
u_char U_D = 10;
u_char nextU_D = 10;

//left right direction
u_char L_R = 10;
u_char nextL_R = 10;

//cyan collison test
u_char a = 10;
u_char aNex=10;
u_char b = 10;
u_char bNex= 10;

signed char Speed = 1;


void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;

  
  secCount ++;
  dsecCount ++;

  if (secCount == 150) {		// once/sec 
    buzzer_set_period(0);

    secCount = 0;
  }
  if(dsecCount==30){
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
	nextU_D += Speed;
	
	buzzer_set_period(500);
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
      //drawPixel(aNex-5,aNex-5,COLOR_BLACK);
      drawPixel(aNex,aNex,COLOR_WHITE);
      L_R = nextL_R;	      
      U_D = nextU_D;
      
      //this is for the collsions with only dots
      if(aNex > nextL_R && aNex < nextL_R + 10 ){
	if( aNex > nextU_D && aNex < nextU_D + 10){
	  drawString5x7(70,70,"ded",COLOR_WHITE,COLOR_BLACK);
	}
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
