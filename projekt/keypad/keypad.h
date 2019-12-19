/*
 * keypad.h
 *
 * Created: 18-12-2019 12:13:21
 *  Author: Bruger
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

void keypadInit();
char ColumnScan();
char ReadRows();
void DecodeKeyboard(char col , char row);
extern char KeyOutput;



#endif /* KEYPAD_H_ */