#ifndef __FREE_FALL_H__
#define __FREE_FALL_H__

extern const int YES;
extern const int NO;

void ff_initialize(void);
int ff_detection(void);
int ff_raw_data(void);

static int calculateVecSum(void);

#endif
