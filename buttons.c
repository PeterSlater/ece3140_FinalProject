#include "MK64F12.h"
#include "buttons.h"

/* SW2 = PTC6*/

const int PRESSED =  1;
const int NOT_PRESSED = 0;

/* Initialize button related hardware */
void btn_initialize(void){
	SIM->SCGC5 |= (1 << 11);
	
	PORTC->PCR[6] |= (1 << 8) | (1 << 1) | (1 << 0);
	
	PTC->PDDR &= ~(1 << 6);
}

/* Returns state of SW2, 1 = pressed, 0 = not pressed */
int btn_SW2_state(void){
	if((PTC->PDIR & (1 << 6)) > 0){
		return NOT_PRESSED;
	}
	
	return PRESSED;
}
