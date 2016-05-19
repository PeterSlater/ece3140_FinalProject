#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"

/* Main loop */
int main(){
	ff_initialize();
	LED_initialize();
	btn_initialize();
	
	while(1){
		debug_printf("%i\r\n", ff_raw_data());
		
		if(ff_detection() > 0){
			debug_printf("Freefall\r\n");
		}
	}
}
