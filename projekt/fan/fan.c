/*
 * fan.c
 *
 * Created: 17-12-2019 08:22:24
 *  Author: Bruger
 */ 
#include <avr/io.h>
#include "../fan/fan.h"
#define FAN_SPEED_MAX 254
#define FAN_SPEED_MED 170
#define FAN_SPEED_LOW 85

void fanInit(){
	
	/*set TCCR2A to fast PWM*/
	//set compare on COM2A1  data sheet 20.10  (page 182) set mode til FAst PWN , 8-bit datasheet 17.2 (page 145)
	TCCR2A |= (1<<COM2A1) | (1<<WGM22) | (1<<WGM20) ; 
	
	// Prescale :64 / cs: 100  datasheet table 20-9 (page 185)
	TCCR2B |= (1<<OCF2A) | (1<<CS22);
	
	 //set   0C2A from port PB4 to output 
	DDRB |= (1<<PB4); 
}


/*global TempC is used to controller the speed of the fan*/
void FanController(float tempC){
	if (tempC < 20.0f)
	{
		OCR2A = FAN_SPEED_LOW;
	}
	if (tempC <= 25.0f && tempC >= 20.0f)
	{
		OCR2A = FAN_SPEED_MED;
	}
	if (tempC > 25.0f)
	{
		OCR2A = FAN_SPEED_MAX ;
	}
}