#ifndef __TIMER_H__
#define __TIMER_H__

/* Represents a time value */
typedef struct {
	unsigned int sec;
	unsigned int msec;
} time_t;

/* Time since timer initialization */
extern volatile time_t current_time;

/* Constant time values */
extern const time_t ZERO_SECONDS;
extern const time_t ONE_SECOND;
extern const time_t TEN_SECONDS;
extern const time_t THIRTY_SECONDS;

/* Sets up hardware and begins counting */
void tmr_initialize(void);

/* Copies the time in the first into the second */
void tmr_copy(volatile time_t*, volatile time_t*);

/* Adds the two times together */
unsigned long tmr_add(volatile time_t*, volatile time_t*);

/* Subracts the first time from the second */
long tmr_subtract(volatile time_t*, volatile time_t*);

/* Unpack the time_t struct to long in milliseconds */
unsigned long tmr_time(volatile time_t*);

#endif
