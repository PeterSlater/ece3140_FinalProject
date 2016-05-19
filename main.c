#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"
#include "timer.h"

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

#define BLUE_WAIT 15000
#define RED_WAIT 1000

/* Main loop */
int main(){
	time_t start = {0,0};
	
	while(1){
		switch(state){
			case INIT:
				ff_initialize();
				btn_initialize();
				LED_initialize();
				tmr_initialize();
				
				/* Transistion to Green */
				state = GREEN;
				start.sec = 0;
				start.msec = 0;
				LED_Off();
				break;
			
			case GREEN:
				LEDGreen_On();
				
				/* Go to Blue if freefall detected */
				if(ff_detection() == YES){
					state = BLUE;
					start.sec = 0;
					start.msec = 0;
				}
				
				LED_Off();
				break;
			
			case BLUE:
				LEDBlue_On();
				
				if(tmr_time(&start) == 0){
					tmr_copy(&current_time, &start);
				}
				
				/* All Ok button pressed or motion detected after some time */
				if(btn_SW2_state() == PRESSED || (ff_motion() == YES && (tmr_subtract(&start, &current_time) > FALL_TIME))){
					state = GREEN;
					start.msec = 0;
					start.sec = 0;
				}
				
				/* Transistion to Red if no motion detected within specified time */
				if(tmr_subtract(&start, &current_time) > BLUE_WAIT){
					state = RED;
					start.msec = 0;
					start.sec = 0;
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
