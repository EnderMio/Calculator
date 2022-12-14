#ifndef _Arduinofunc_H_
#define _Arduinofunc_H_

#ifndef EBUG
#include <LiquidCrystal_I2C.h>
void lcd_lineclear(LiquidCrystal_I2C* lcd, int col, int line, int end);
#endif
bool is_num(char c);
bool is_func(char c);
bool is_calc(char c);

#endif