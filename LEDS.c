#include "MK64F12.h"

/* Initialized LED related hardware */
void LED_initialize(void) {
  SIM->SCGC5 |= (1 << 10) | (1 << 13);
  
	PORTB->PCR[22] = 1 << 8;
  PORTB->PCR[21] = 1 << 8;
  PORTE->PCR[26] = 1 << 8;
  
  PTB->PDOR = (1 << 21) | (1 << 22);
  PTB->PDDR = (1 << 21) | (1 << 22);

  PTE->PDOR = 1 << 26;
  PTE->PDDR = 1 << 26;
}


/* Turns on red LED */
void LEDRed_On (void) {
  PTB->PCOR   = 1 << 22;
}

/* Turns on green LED */
void LEDGreen_On (void) {
  PTE->PCOR   = 1 << 26;
}

/* Turns on blue LED */
void LEDBlue_On (void) {
  PTB->PCOR   = 1 << 21;
}

/* Turn off all LEDs */
void LED_Off (void) {
  PTB->PSOR   = 1 << 22;
  PTB->PSOR   = 1 << 21;
  PTE->PSOR   = 1 << 26;
}

void delay(void){
	int j;
	for(j=0; j<10000000; j++);
}
