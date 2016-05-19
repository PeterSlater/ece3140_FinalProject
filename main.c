#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"

/*
 * Program State variable
 * 	0 = Initialize
 *	1 = Green, All Ok
 *	2 = Blue, Possibly Not Ok
 *	3 = Red, Critical
 */
 
volatile int state = 0;
#define INIT 0
#define GREEN 1
#define BLUE 2
#define RED 3

/* Main loop */
int main(){
	while(1){
		switch(state){
			case INIT:
				ff_initialize();
				btn_initialize();
				LED_initialize();
				
				/* Transistion to Green */
				state = GREEN;
				LED_Off();
				break;
			
			case GREEN:
				LEDGreen_On();
				
				/* Go to Blue if freefall detected */
				if(ff_detection() == YES){
					state = BLUE;
				}
				
				LED_Off();
				break;
			
			case BLUE:
				LEDBlue_On();
				
				/* Transistion to Red if help needed */
				state = RED;
			
				/* All Ok button pressed */
				if(btn_SW2_state() == PRESSED){
					state = GREEN;
				}
				
				LED_Off();
				break;
			
			case RED:
				LEDRed_On();
				
				/* Wait for All Ok button to be pressed */
				if(btn_SW2_state() == PRESSED){
					state = GREEN;
				}
				
				LED_Off();
				break;
			
			default:
				debug_printf("Unknown State, will reset");
			
				/* Transistion to Init, attempt to fix the problem*/
				state = INIT;
			
				break;
		}
	}
}
