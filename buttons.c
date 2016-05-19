// If SW2 is pressed, clear all
// -> Return to ready detecting state 
// -> Turn LED back to Green

// If S

#include "MK64F12.h"

void Button2_Setup(void){
	PORTC->PCR[6] = (1 << 8);
	PORTC->PCR[6] = (PORTC->PCR[6] & ~ PORT_PCR_IRQC_MASK) | ((0x9 << 16) & PORT_PCR_IRQC_MASK);
	NVIC_EnableIRQ(PORTC_IRQn);
}

