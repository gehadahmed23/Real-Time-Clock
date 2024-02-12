/*
 * Timer.h
 *
 * Created: 2/6/2024 8:18:14 AM
 *  Author: Dell
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer_CTC_init_interrupt(void);
void timer_wave_nonPWM(void);
void timer_wave_fastPWM(void);
void timer_wave_phasecorrectPWM(void);
void timer2_overflow_init_interrupt(void);

#endif /* TIMER_H_ */