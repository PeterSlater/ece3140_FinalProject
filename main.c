// Green 	- good
// Blue 	- fall occurs
// Red 		- something bad happened...

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
#include "LEDS.h"
#include "free_fall.h"
#include "buttons.h"

int main(){
	
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize(); // Take out?
	
	LEDGreen_On();	// Ready
	ff_detection();	// begin FF detection
	
	
	
	
	
	}
