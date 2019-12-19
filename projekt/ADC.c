/*
 * ADC.c
 *
 * Created: 10-12-2019 09:40:17
 *  Author: Bruger
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include "ADC.h"
#include <util/delay.h>
#include "lcd.h"
#include "fan.h"
#include "led.h"
 

void ADCInit(){
	ADMUX |= (1 << REFS0); // 5V supply used for ADC reference, select ADC channel 0, datasheet 26.8.1
	DIDR0 = (1 << ADC0D);  // disable digital input on ADC0 pin, datasheet 26.8.2
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
}

void udskrivningintro(){
	
	float tempC = 0;
	char buffer[7];
	/* initialize display, cursor on */
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);

	/* clear display and home cursor */
	lcd_clrscr();
	
	/* put string to display (line 1) with linefeed */
	lcd_puts("Temp i hus er");
	
	/* move cursor to position 15 on line 1 */
	lcd_gotoxy(15,0);
	
	/* write single char to display */
	lcd_putc(':');

	/* cursor is now on second line, write second line */
	lcd_puts("/n");
	
	
	if (!(ADCSRA & (1 << ADSC)))
	{
		unsigned int ADC_data;
		float tempK;
		float temp;
		ADC_data = ADC;								// get the ADC value, datasheet 28.9.3
		temp = log(10000.0 * ((1024.0/ADC_data) - 1));
		tempK = 1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
		tempC = tempK-273.15 ;
		dtostrf(tempC,3,1,buffer);
		lcd_gotoxy(0,1);
		lcd_puts(buffer);
		lcd_puts(" C");
		FanController(tempC);
		colorControl(tempC);
		ADCSRA |= (1 << ADSC);						// start the next ADC conversion
	}
	
}