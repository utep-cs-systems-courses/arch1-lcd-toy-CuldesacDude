#INCLUDE <MSP430.H>
#INCLUDE "LIBtIMER.H"
#INCLUDE "BUZZER.H"

VOID BUZZER_INIT()
{
  /* 
       dIRECT TIMER a OUTPUT "ta0.1" TO p2.6.  
        aCCORDING TO TABLE 21 FROM DATA SHEET:
          p2sel2.6, p2sel2.7, ANMD p2sel.7 MUST BE ZERO
          p2sel.6 MUST BE 1
        aLSO: p2.6 DIRECTION MUST BE OUTPUT
  */
  TIMERauPMODE();/* USED TO DRIVE SPEAKER */
  p2sel2 &= ~(bit6 | bit7);
  p2sel &= ~bit7;
  p2sel |= bit6;
  p2dir = bit6;/* ENABLE OUTPUT TO SPEAKER (p2.6) */
}

VOID BUZZER_SET_PERIOD(SHORT CYCLES) /* BUZZER CLOCK = 2mhZ.  (PERIOD OF 1K RESULTS IN 2KhZ TONE) */
{
  ccr0 = CYCLES;
  ccr1 = CYCLES >> 1;/* ONE HALF CYCLE */
}






