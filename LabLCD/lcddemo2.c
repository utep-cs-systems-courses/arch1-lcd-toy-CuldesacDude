#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>
/** Initializes everything, clears the screen, draws "hello" and a square */

int main(){
  configureClocks();
  lcd_init();
  
  u_char offset_r = 50, offset_c = 50;
  
  clearScreen(COLOR_BLUE );

  //fillRectangle(50,50, 60, 60, COLOR_WHITE);  
  // draw trianagle
  offset_r = 50;
  offset_c = 50;
  for(int r=0; r<=50; r++){ // this line determines the pixel count
    for(int c =0; c<=r; c++){

      drawPixel(offset_c+c+r/c, offset_r+r-c/r, COLOR_RED);
      
    }
  }
  //pointing up
  offset_r = 50;
  offset_c = 20;
  for(int r=0; r<=40; r++){ // this line determines the pixel count
    for(int c =0; c<=r; c++){
      
      drawPixel(offset_c+r+c, offset_r+c-r, COLOR_ORANGE);
      
    }
  }

  offset_r = 50;
  offset_c = 20;
  for(int r=0; r<=40; r++){ // this line determines the pixel count
    for(int c =0; c<=r; c++){
      
      drawPixel(offset_c+r-c, offset_r+c+r, COLOR_YELLOW);
      
    }
  }

  offset_r = 50;
  offset_c = 100;
  for(int r=0; r<=40; r++){ // this line determines the pixel count
    for(int c =0; c<=r; c++){
      
      drawPixel(offset_c-r+c, offset_r+c+r, COLOR_BLUE);
      
    }
  }
  //point facing left
  offset_r = 100;
  offset_c = 20;
  for(int r=0; r<=40; r++){ // this line determines the pixel count
    for(int c =0; c<=r; c++){
      
      drawPixel(offset_c+c+r, offset_r+r-c, COLOR_WHITE);
      
    }
  }
}
