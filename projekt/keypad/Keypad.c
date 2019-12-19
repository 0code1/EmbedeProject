/*
 * Keypad.c
 *
 * Created: 18-12-2019 12:13:05
 *  Author: Bruger
 */ 
#define F_CPU 16000000UL
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../ADC/ADC.h"
#include "../lcd/lcd.h"
#include <string.h>

#define COLS_PORT PORTK |= (1<<PK0) | (1<<PK1) | (1<<PK2) | (1<<PK3);
#define DELAY1 50


void keypadInit()
{
	//input port enable pull-up
	PORTK |= (1<<PK4) | (1<<PK5) |(1<<PK6) | (1<<PK7) ;
	// OutPut
	DDRK |= (1<<PK0) | (1<<PK1) | (1<<PK2) | (1<<PK3);
	
	 lcd_init(LCD_DISP_ON_CURSOR_BLINK);
}

char ColumnScan() // scan column med en static number
{
	COLS_PORT; // set all port til 1
	static int columnCounter = 1;
	
	if (columnCounter == 1)
	{
		PORTK &= ~(1<<PK0);
		columnCounter++;
		return 1;
	}
	if (columnCounter == 2)
	{
		PORTK &= ~(1<<PK1);
		columnCounter++;
		return 2;
	}
	if (columnCounter == 3)
	{
		PORTK &= ~(1<<PK2);
		columnCounter++;
		return 3;
	}
	if (columnCounter == 4)
	{
		PORTK &= ~(1<<PK3);
		columnCounter = 1;
		return 4;
	}
	
}

char ReadRows() // check if the button is push
{
	if (~PINK  & (1 << PK4)) // check om denne er blive tryk
	{
		 _delay_ms(DELAY1); // delay for at denne ikke blive tryk flere gang *overflow*
		if (~PINK & (1<<PK4)) //  check igen om denne er tryk og returner værdig , denne vil stadig blive skrive om denne ikke er tryk på grund af memori før delay
		{
			return 1;
		}
	}
	if (~PINK  & (1 << PK5))
	{
		 _delay_ms(DELAY1);
		if (~PINK & (1<<PK5))
		{
			return 2;
		}
	}
	if (~PINK  & (1 << PK6))
	{
		 _delay_ms(DELAY1);
		if (~PINK & (1<<PK6))
		{
			return 3;
		}
	}
	if (~PINK  & (1 << PK7))
	{
		 _delay_ms(DELAY1);
		if (~PINK & (1<<PK7))
		{
			return 4;
		}
	}
	return 0;
}



void DecodeKeyboard(char col , char row){
	
	 char ud[4][4] = {{'D', 'C', 'B' , 'A'}, {'#', '9','6','3'},{'0', '8', '5', '2'},{'*','7','4','1'}}; // array
		 
	if (row != 0)
	{
	  char input[2] = "";
	  char counter = 0 ;

	  if (counter < 2)
	  {
		  char KeyOutput = ud[col-1][row-1];
		  char string[] = {KeyOutput, '\0'};
		  strcat(input, string);
		  lcd_clrscr();
		  lcd_puts(input);
		  counter++;
		  if (counter > 2)
		  {
			  counter = 0 ;
			  input[0] = '\0';
		  }
	  }
	}
}






