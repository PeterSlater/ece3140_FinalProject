#include "MK64F12.h"
#include "timer.h"

/* Constant load value that represents a millisecond */
#define MILLISECOND 54000

/* Time since timer initialization */
volatile time_t current_time = {0, 0};

/* Constant time values */
const time_t ZERO_SECONDS = {0, 0};
const time_t ONE_SECOND = {.sec = 1, .msec = 0};
const time_t TEN_SECONDS = {.sec = 10, .msec = 0};
const time_t THIRTY_SECONDS = {.sec = 30, .msec = 0};

/* Sets up hardware and begins counting */
void tmr_initialize(void){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->CHANNEL[1].TCTRL = 0;
	PIT->MCR = 0;
	PIT->CHANNEL[1].LDVAL = MILLISECOND;
	PIT->CHANNEL[1].TCTRL |= (1 << 0) | (1 << 1);
	
	NVIC_EnableIRQ(PIT1_IRQn);
	
	current_time.sec = 0;
	current_time.msec = 0;
	
	NVIC_SetPriority(PIT1_IRQn, 0);
}

/* IRQ Handler for PIT 1 */
void PIT1_IRQHandler(void) {
	char o;
	
	o = (PIT->CHANNEL[1].TFLG & 0x01);
	PIT->CHANNEL[1].TFLG = o;
	
	if(current_time.msec >= 999){
		current_time.sec = current_time.sec + 1;
		current_time.msec = 0;
	} else {
		current_time.msec += 1;
	}
	
	PIT->CHANNEL[1].TCTRL = 0;
	PIT->CHANNEL[1].LDVAL = MILLISECOND;
	PIT->CHANNEL[1].TCTRL |= (1 << 0) | (1 << 1);
}

/* Copies the time in the first into the second */
void tmr_copy(volatile time_t* t1, volatile time_t* t2){
	t2->sec = t1->sec;
	t2->msec = t1->sec;
}

/* Adds the two times together */
unsigned long tmr_add(volatile time_t* t1, volatile time_t* t2){
	unsigned int sec = 0;
	unsigned int msec = 0;
	time_t t = {0,0};
	
	sec = t1->sec + t2->sec;
	msec = t2->msec + t2->msec;
	
	if(msec >= 1000){
		msec = msec - 1000;
		sec = sec + 1;
	}
	
	t.sec = sec;
	t.msec = msec;
	
	return tmr_time(&t);
}

/* Subracts the first time from the second */
long tmr_subtract(volatile time_t* t1, volatile time_t* t2){
	return (long)(tmr_time(t2) - tmr_time(t1));
}

/* Unpack the time_t struct to long in milliseconds */
unsigned long tmr_time(volatile time_t* t){
	return (t->sec) * 1000 + t->msec;
}
