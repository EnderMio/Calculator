#include "arduinofunc.h"
void lcd_lineclear(LiquidCrystal_I2C* lcd, int col, int line, int end) {
    lcd->setCursor(col, line);
    for (int i = 0; i <= end - col; i++) lcd->print(' ');
    lcd->setCursor(col, line);
}
bool is_num(char c) {
    return c >= '0' && c <= '9';
}
bool is_func(char c) {
    return c == '(' || c == 's' || c == 'c' || c == 'e' || c == 'l';
}
bool is_calc(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}