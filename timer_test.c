#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"
#include "timer.h"

/* Main loop */
int main(){
	time_t start = {0,0};
	
	LED_initialize();
	ff_initialize();
	btn_initialize();
	tmr_initialize();
	
	while(1){
		LEDBlue_On();
		tmr_copy(&current_time, &start);
		while(tmr_subtract(&start, &current_time) <= 1000);
		
		LED_Off();
		tmr_copy(&current_time, &start);
		while(tmr_subtract(&start, &current_time) <= 1000);
	}
}
