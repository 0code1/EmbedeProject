#define F_CPU 16E6
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../keypad/keypad.h"
#include "../lcd/lcd.h"
#include "../timer/timer.h"
#include "../ADC/ADC.h"
#include "../fan/fan.h"
#include "../led/led.h"

#define SET_TIMER_2 50
#define DELAY 100

//timer_second
ISR(TIMER1_COMPB_vect)
{
	Udskrive_temp();// Display the temperature on the lcd med 1 second interval
}

//timer_millisecond
ISR(TIMER0_COMPA_vect){
FanController(tempC);
colorControl(tempC); //setting the fan speed at 0,5 sec interval
}


int main(void)
{
	UartInit();
	ADCInit();
	fanInit();
	ledInit();
	keypadInit();
	Timer_Second();
	Timer_Millisecond(SET_TIMER_2);
	sei();
	
	while (1)
	{
		
		//char row;
		//char column;
		//row = ReadRows();
		//_delay_ms(DELAY);
		//column = ColumnScan();
		//DecodeKeyboard(column, row);
	}
}