#include <msp430.h>
#include "stateMachines.h"

char count = 0;
char dimState = 0;
char sirenState = 0;
/*as button is pressed we increment to three starting from 0 and prints onto the lcd screen*/
void countToThree()
{
  switch(count){
    /*0*/
  case 0:
    drawString11x16(20, 10,"0", COLOR_WHITE, COLOR_BLACK);
    count++;
    break;

  case 1:
    drawString11x16(20, 35,"1", COLOR_WHITE, COLOR_BLACK);
    count++;
    break;

  case 2:
    drawString11x16(20, 60, "2", COLOR_WHITE, COLOR_BLACK);
    count++;
    break;

  case 3:
    drawString11x16(20, 85, "3", COLOR_WHITE, COLOR_BLACK);
    count++;
    break;

  default:
    clearScreen(COLOR_BLACK);
    count = 0;
  }
}
/*dims lights to 75%, as we call dimLights() really fast through the wdInterrupt one state
  will be off as to achieve the desired effect of 75%*/

short convertPeriod(short pd)
{
  return 2000000/pd;
}
/*
short asPeriod(short pd)
{
  if(pd <= 1500){
    pd += 200;
    return pd;
  }else{
    pd -= 200;
    return pd;
  }}
*/
 /*will continuously annoy your ears until the period reaches 0 where it will start all over*/
void siren()
{
  static short period = 1500;
  switch(sirenState){
  case 0:
    period = asPeriod(period); /*increment the annoying sound*/
    break;
  case 1:
    period = asPeriod(period); /*then decrement*/
    break;
  }
  short sirenHz = convertPeriod(period); /*convert period into Hz*/
  buzzer_set_period(sirenHz);
}
/*advances our shape state with different colors*/
void sirenShapeAdvance()
{
  switch(sirenState){
  case 0:
    drawDiamond(screenWidth/2, 0);
    break;
  case 1:
    drawDiamond(screenWidth/2, 1);
    break;
  }
}
/*
void sirenStateAdvance()
{
  switch(sirenState){
  case 0:
    siren();
    sirenShapeAdvance();
    sirenState++;
    break;
  case 1:
    siren();
    sirenShapeAdvance();
    sirenState--;
    break;
  }
}
*/

 /*resets everything, lights will be reset, the count will be reset, but the button will need to be 
   held if you want buzzer to be off*/
void reset()
{
  clearScreen(COLOR_BLACK);
  bttnState = 0;
  buzzer_set_period(0);
  count = 0;
  green_on = 0;
  led_update();
}
/*red will be on for 75% of the time*/
void dim75()
{
  switch(dimState){
  case 0:
    red_on = 1;
    dimState++;
    break;
  case 1:
  case 2:
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_update();
}
