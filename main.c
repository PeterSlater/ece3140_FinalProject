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
//#include "MK64F12.h"

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
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize();
	
	// To-do: configure non static register read/write
	// To-do: configure interrupt service routine setup on board
	
	// Issue soft reset
	
	// Initialize reference set to 0g for all axes
	
	// Enable interrupts using CTRL_REG4
	
	// Route interrupts to INT1/2 pin using CTRL_REG5
	// FXOS8700CQ INT1 -> PTC6
	// FXOS8700CQ INT2 -> PTC13
	
	
	// Wait for INT1/2 to assert, ISR to flash LED and clear interrupt by reading register TRANSIENT_SRC
	int retVal;
	uint8_t who = 0;
  retVal = Register_Read_Top(0x0D, &who);
  if (retVal == 0) {
    if (who != 0xC7) {
      debug_printf("Device Failed to connect");                       /* Wrong ID */
    }
  }
	
	while(1){
		Accelerometer_GetState(&state);
		Magnetometer_GetState(&mstate);
		debug_printf("%4d %5d %5d %5d %5d %5d %5d\r\n", who, state.x, state.y, state.z, mstate.x, mstate.y, mstate.z);
	}
}
