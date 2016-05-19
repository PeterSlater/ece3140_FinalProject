#include <fsl_debug_console.h>

#include "MK64F12.h"
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"

/* Main loop */
int main(){
	ff_initialize();
	btn_initialize();
	LED_initialize();
	
	while(1){
		debug_printf("%i\r\n", btn_SW2_state());
	}
}
