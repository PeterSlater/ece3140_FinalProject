#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"

/* Main loop */
int main(){
	LED_initialize();
	btn_initialize();
	ff_initialize();
	
	while(1){
		/* Test blue led on */
		LEDBlue_On();
		delay();
		LED_Off();
		delay();
		
		/* Test green led on */
		LEDGreen_On();
		delay();
		LED_Off();
		delay();
		
		/* Test red led on */
		LEDRed_On();
		delay();
		LED_Off();
		delay();
		
		/* Test all leds on */
		LEDRed_On();
		LEDGreen_On();
		LEDBlue_On();
		delay();
		LED_Off();
		delay();
	}
}
