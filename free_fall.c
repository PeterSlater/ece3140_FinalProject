#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <fsl_debug_console.h>
#include <board.h>
#include <math.h>

#include "MK64F12.h"
#include "free_fall.h"

/* Expirementally determined free fall and motion detection thresholds */
#define FREE_FALL_THRESHOLD 350
#define MOTION_THRESHOLD 150

/* Constants used to intrepret return values */
const int YES = 1;
const int NO = 0;
const int FALL_TIME = 1000;

static ACCELEROMETER_STATE state;
static MAGNETOMETER_STATE mstate;

/* Initialized the hardware */
void ff_initialize(void){
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize();
}

/* Returns 1 if free fall condition met, zero otherwise*/
int ff_detection(void){
	int vecSum = calculateVecSum();
			
	if(vecSum < FREE_FALL_THRESHOLD){
		return YES;
	}
	
	return NO;
}

/* Returns 1 if motion condition met, zero otherwise */
int ff_motion(void){
	int vecSum = calculateVecSum();
	
	if(abs(vecSum - 1000) > MOTION_THRESHOLD){
		return YES;
	}
	
	return NO;
}

/* Returns the raw vector sum of the acceleration */
int ff_raw_data(void){
	return calculateVecSum();
}

/* Reads data and calcuates the vector sum of the acceleration */
static int calculateVecSum(void){
	int vecSum;
	
	Accelerometer_GetState(&state);
	Magnetometer_GetState(&mstate);
	
	vecSum = sqrt(state.x * state.x + state.y * state.y + state.z * state.z);
	
	return vecSum;
}
