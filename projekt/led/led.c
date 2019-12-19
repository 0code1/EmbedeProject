/*
 * led.c
 *
 * Created: 17-12-2019 16:51:41
 *  Author: Bruger
 */ 
#include <avr/io.h>
#define LIGHT_ON 255
#define LGHT_OFF 0

void ledInit(){
	// Compare Output Mode: Fast PWM Mode: Clear OC4A OC4B OC4C on Compare Match, set OC0A at BOTTOM, non-invertingvoid  mode (Table 16-3)
	TCCR4A |= (1<<COM4A1) |(1<<COM4B1) | (1<<COM4C1);
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM0 = 1, WGM1 = 1 (Table 16-8)
	TCCR4A |= (1<<WGM42) | (1<<WGM40);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 datasheet table 17-6, frekv. = 980Hz
	TCCR4B |= (1<<CS41) | (1<<CS40);
	
	// set output port 
	DDRH |= (1<<PH4) | (1<<PH5) | (1<<PH3) ;
}

void colorControl(float tempC){
	if (tempC < 20.0f)
	{
		OCR4C = LIGHT_ON;
		OCR4B = LGHT_OFF;
		OCR4A = LGHT_OFF;
	}
	if (tempC > 25.0)
	{
		OCR4B = LGHT_OFF;
		OCR4A = LIGHT_ON;
		OCR4C = LGHT_OFF;
	}
	if (tempC <= 25.0 && tempC >= 20.0)
	{
		OCR4A = LGHT_OFF;
		OCR4C = LGHT_OFF;
		OCR4B = LIGHT_ON;
	}
}