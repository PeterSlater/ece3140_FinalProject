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

#ifdef RTE_CMSIS_RTOS
#include "cmsis_os.h"
#endif

#ifndef FXOS8700_I2C_PORT
#define FXOS8700_I2C_PORT       0
#endif

#ifndef FXOS8700_I2C_ADDR
#define FXOS8700_I2C_ADDR       0x1D
#endif

/* I2C Driver */
#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n) _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(FXOS8700_I2C_PORT);
#define ptrI2C         (&I2C_Driver_(FXOS8700_I2C_PORT))

ACCELEROMETER_STATE state;
MAGNETOMETER_STATE mstate;

int32_t Register_Read_Top (uint8_t reg, uint8_t *val) {
  uint8_t data[1];

  data[0] = reg;
  ptrI2C->MasterTransmit(FXOS8700_I2C_ADDR, data, 1, true);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) { return -1; }
  ptrI2C->MasterReceive (FXOS8700_I2C_ADDR, val, 1, false);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) { return -1; }

  return 0;
}

int32_t Register_Write_Top (uint8_t reg, uint8_t val) {
  uint8_t data[2];

  data[0] = reg;
  data[1] = val;
  ptrI2C->MasterTransmit(FXOS8700_I2C_ADDR, data, 2, false);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 2) { return -1; }

  return 0;
}

/*
ISR Config
*/

int main(){
	int vecSum;
	int i = 0;
	
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize();
	Register_Write_Top(0x2A, 0x00);				// Put this in standby mode
	// To-do: configure non static register read/write - Done
	// To-do: configure interrupt service routine setup on board
	
	// ID Check:
	int retVal;
	uint8_t who = 0;
  retVal = Register_Read_Top(0x0D, &who);
  if (retVal == 0) {
    if (who == 0xC7) {
      debug_printf("Device Initialized");                       /* Correct ID */
    }
  }
	
	// Enable interrupts using CTRL_REG4
	//Register_Write_Top(0x2D, 0x04);
	
	// Freefall/motion detection interrupt routing to INT1; FXOS8700CQ INT1 -> PTC6; FXOS8700CQ INT2 -> PTC13
	//Register_Write_Top(0x2E, 0x04);
	
	// Freefall configurations
	Register_Write_Top(0x15, 0x38); // Freefall/Motion Configuration Register
	Register_Write_Top(0x17, 0x10);	// Threshold
	
	// Wait for INT1/2 to assert, ISR to flash LED and clear interrupt by reading register TRANSIENT_SRC
	
	
	// enable interrupts for the feature using CTRL_REG4
	// Register checks
	uint8_t ffmocofig = 0;
	uint8_t threshcofig = 0;
	Register_Read_Top(0x15, &ffmocofig);
	Register_Read_Top(0x17, &threshcofig);
	debug_printf("0x%08x\n 0x%08x\n", ffmocofig,  threshcofig);
	Register_Write_Top(0x2A, 0x01);			// Put this in active mode
	
	while(1){
		Accelerometer_GetState(&state);
		Magnetometer_GetState(&mstate);	
		
		uint8_t freefall = 0;
		Register_Read_Top(0x16, &freefall);
		/*if (freefall != 0){
			//debug_printf("Freefall!"); 
			//debug_printf("0x%08x\n", freefall); 
		}*/
		//debug_printf("0x%08x\n", freefall); 
		//debug_printf("%5d %5d %5d %5d %5d %5d\r\n", state.x, state.y, state.z, mstate.x, mstate.y, mstate.z);
		
		vecSum = sqrt(state.x * state.x + state.y * state.y + state.z * state.z);
		
		if (vecSum < 350){
			debug_printf("Freefall!"); 
		}
		
		
		//debug_printf("%5d\r\n", vecSum);
		
		for(i = 0; i < 1000; i++);
	}
}
