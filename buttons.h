#ifndef __BUTTONS_H__
#define __BUTTONS_H__

extern const int PRESSED;
extern const int NOT_PRESSED;

void btn_initialize(void);
int btn_SW2_state(void);
void btn_SW2_register_ISR(void *(isr)(void));

#endif
