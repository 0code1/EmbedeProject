/*
 * timer.c
 *
 * Created: 09-12-2019 15:48:35
 *  Author: Bruger
 */ 

#define F_CPU 16000000UL
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define CALCULATED_TIMER 
#define TO_SECOND 

void Timer_Second()
{
	TCCR1B |= (1<<WGM12);			// Mode 4, CTC = WGM10 - WGM13 = 0100, Table 20-6 (page 176)
	TIMSK1 |= (1<<OCIE1B);			// Timer/Counter1, Output Compare B Match Interrupt Enable, 20.15.8 (page 184)
	OCR1A = 15624;				// 1 sec. between irq
	TCCR1B |= (1<<CS10)|(1<<CS12);	        // Prescaler: 1024, CS=101, Table 17-6 (page 157)
	
}

void Timer_Millisecond(unsigned int ms)
{
	TCCR0B |= (1<<WGM02);				// Mode 4, CTC = WGM10 - WGM13 = 0100, Table 20-6 (page 176)
	TIMSK0 |= (1<<OCIE0A);				// Timer/Counter1, Output Compare A Match Interrupt Enable, 20.15.8 (page 184)
	OCR0A = (ms * (F_CPU / 1000) / 1024) - 1 ;	// OCR0A = (Tdelay * F_CPU / N) - 1 => 61.5 gives 1ms => 62499 gives 1s
	TCCR0B |= ((1<<CS02) |(1<<CS00));				// Prescaler: 1024, CS=011, Table 20-7 (page 177). Timer starts!
}