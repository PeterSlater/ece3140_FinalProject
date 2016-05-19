#include <Board_Accelerometer.h>	// Interface with accelerometer
#include <Board_Magnetometer.h>		// Interface with magnetometer
#include <fsl_debug_console.h>
#include "Driver_I2C.h"
#include "Board_Accelerometer.h"
#include "Board_Magnetometer.h"
#include "RTE_Components.h"
#include <board.h>
#include <math.h>
#include "MK64F12.h"
#include "utils.h"
#include "free_fall.h"

ACCELEROMETER_STATE state;
MAGNETOMETER_STATE mstate;

void ff_detection(void){
	int vecSum;
	while(1){
		Accelerometer_GetState(&state);
		Magnetometer_GetState(&mstate);	
		vecSum = sqrt(state.x * state.x + state.y * state.y + state.z * state.z);
			
		if (vecSum < 350){
			debug_printf("Probably Freefall..."); 
			LEDBlue_On();
			//if (slow_movement && impact){
			//	LED_BlinkCray();
			//}
			delay();
		}
	}
}