/** \file shapemotion.c
 *  \brief This is a simple shape motion demo.
 *  This demo creates two layers containing shapes.
 *  One layer contains a rectangle and the other a circle.
 *  While the CPU is running the green LED is on, and
 *  when the screen does not need to be redrawn the CPU
 *  is turned off along with the green LED.
 */
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>

#define GREEN_LED BIT6

const int squareSize = 10;

AbRect rect5 = {abRectGetBounds, abRectCheck, {squareSize,squareSize}}; /**< 10x10 rectangle */
AbRArrow rightArrow = {abRArrowGetBounds, abRArrowCheck, 10};

//this below is the black outlines
AbRectOutline fieldOutline = {/* playing field */
  abRectOutlineGetBounds, abRectOutlineCheck,
  {screenWidth/2-5, screenHeight/2-5}
  
};

//this is the Arrow in the middle
/*Layer layer4 = {
  (AbShape *)&rightArrow,
  {(screenWidth/2)+5, (screenHeight/2)+5}, //< bit below & right of center 
  {3,0}, {0,0},    // last & next pos 
  COLOR_WHITE
  };  

Layer layer3 = {//CIRCLE
  (AbShape *)&circle2,
  {(screenWidth/2)+5, (screenHeight/2)+5},
  {0,0}, {0,0},  
  COLOR_RED,
  &layer4,
};

Layer layer1 = {
  (AbShape *)&rect5,
  {screenWidth/2, screenHeight/2},
  {0,0}, {0,0},  
  COLOR_RED,
  &fieldLayer,
};
*/

Layer fieldLayer = {
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2},
  {0,0}, {0,0},  
  COLOR_RED,
  0,
};


Layer layer0 = {/**< Layer with an orange circle */

  (AbShape *)&circle14,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /**< bit below & right of center */
  {0,0}, {0,0},    /* last & next pos */
  COLOR_BLUE,
  &fieldLayer,
};

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/* initial value of {0,0} will be overwritten */

/*MovLayer ml4 = { &layer4, {1,0}, 0 };
MovLayer ml3 = { &layer3, {1,1}, &ml4 };
MovLayer ml1 = { &layer1, {1,2}, &ml3 };*/

const int u = 1;

int *u_c;

MovLayer ml0 = { &layer0, {  u, 0  }, 0 };

void movLayerDraw(MovLayer *movLayers, Layer *layers){

  int row, col;
  MovLayer *movLayer;

  and_sr(~8);/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);/**< disable interrupts (GIE on) */


  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer;
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break;
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color);
      } // for col
    } // for row
  } // for moving layer being updated
}



//Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}}; /**< Create a fence region */

/** Advances a moving shape within a fence
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 */
void mlAdvance(MovLayer *ml, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for (; ml; ml = ml->next) {
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||

	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {

	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];//inverts velocity

	newPos.axes[axis] += (2*velocity);
      }/**< if outside of fence */
    } /**< for axis */
    ml->layer->posNext = newPos;
  } /**< for ml */
}


u_int bgColor = COLOR_BLACK;     /**< The background color */
int redrawScreen = 1;           /**< Boolean for whether screen needs to be redrawn */

Region fieldFence;/**< fence around playing field  */


/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
void main()
{
  P1DIR |= GREEN_LED;/**< Green led on when CPU on */
  P1OUT |= GREEN_LED;
  
  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(1);
  shapeInit();
  layerInit(&layer0);
  layerDraw(&layer0);
  
  layerGetBounds(&fieldLayer, &fieldFence);


  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */


  for(;;) {
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);      /**< CPU OFF */
    }
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
    redrawScreen = 0;
    movLayerDraw(&ml0, &layer0);
  }
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  static short count = 0;
  P1OUT |= GREEN_LED;      /**< Green LED on when cpu on */
  count ++;
  if (count == 5) {//15
    mlAdvance(&ml0, &fieldFence);
    
    u_c = &u;
    *u_c = 0; 
    //printf("u = %d\n", u);
    if (p2sw_read())
      redrawScreen = 1;
    count = 0;
  }
  P1OUT &= ~GREEN_LED;    /**< Green LED off when cpu off */
}
