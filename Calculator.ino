#include <IRremote.h>//红外
#include <LiquidCrystal_I2C.h>//液晶屏
#include "calculator.h"
LiquidCrystal_I2C lcd(0x20, 16, 2);//显示屏初始化 2行16列
int RECV_PIN = 11;//定义红外接收接口11
IRrecv irrecv(RECV_PIN);
decode_results results;
int x;//第二行正在输入位置光标
bool shift_flag, reset_flag, sign_flag, vaNum, isNeg;
int ykh_flag;//定义shift标记 右括号合法标记
string *str = string_build();
void calc_init() {
    reset_flag = x = vaNum = isNeg = ykh_flag = shift_flag = 0;
    sign_flag = 1;
    string_add(str, "(");
    lcd_lineclear(&lcd, 0, 0, 15);
    lcd.print("Imput:");
    lcd_lineclear(&lcd, 0, 1, 15);
}
void setup() {
    lcd.init();// LCD初始化设置
    lcd.backlight();// 打开 LCD背光
    irrecv.enableIRIn();//启动红外接收
    Serial.begin(9600);//设置串口波特率9600
    calc_init();
}
void loop()
{
    if ((irrecv.decode(&results) || Serial.available()) && !reset_flag)
    {
        char c;
        if(Serial.available()) c = Serial.read();
        else Serial.println(results.value, HEX);// results.value为红外遥控信号的具体数值
        if (results.value == 0xFD30CF) c = '0';
        if (results.value == 0xFD08F7) c = '1';
        if (results.value == 0xFD8877) c = '2';
        if (results.value == 0xFD48B7) c = '3';
        if (results.value == 0xFD28D7) c = '4';
        if (results.value == 0xFDA857) c = '5';
        if (results.value == 0xFD6897) c = '6';
        if (results.value == 0xFD18E7) c = '7';
        if (results.value == 0xFD9867) c = '8';
        if (results.value == 0xFD58A7) c = '9';
        if (results.value == 0xFDB04F) c = '=';
        if(!shift_flag) {
            if (results.value == 0xFD20DF) c = '+';
            if (results.value == 0xFDA05F) c = '-';
            if (results.value == 0xFD609F) c = '*';
            if (results.value == 0xFD10EF) c = '(';
            if (results.value == 0xFD906F) c = ')';
            if (results.value == 0xFD50AF) c = '/';
        }
        else {
            if (results.value == 0xFD20DF) c = 'l';
            if (results.value == 0xFDA05F) c = '^';
            if (results.value == 0xFD609F) c = 'e';
            if (results.value == 0xFD10EF) c = 's';
            if (results.value == 0xFD906F) c = 'c';
            if (results.value == 0xFD50AF) c = 'p';
        }
        if (results.value == 0xFD708F)//按st/rept shift模式
        {
            shift_flag = !shift_flag;//shift开关
            lcd.setCursor(15, 0);
            lcd.print(shift_flag ? "^" : " ");
            lcd.setCursor(x, 1);
        }
        else if(c >= '0' && c <= '9') {//NUM
            if(sign_flag) {
                if(!isNeg) string_add(str, " ");
                sign_flag = isNeg = 0;
            }
            if(str->vol[str->len - 1] == '0' && !vaNum) {
                lcd.setCursor(x - 1, 1);              
                str->vol[str->len - 1] = c;
            }
            else {
                x++;
                if(c != '0') vaNum = 1;
                char s[2] = {c, '\0'};
                string_add(str, s);
            }
            lcd.print(c);
        }
        else if(is_calc(c) || c == '^') {//SIGN
            if(sign_flag && (is_calc(str->vol[str->len - 1]) || str->vol[str->len - 1] == '^')) str->vol[str->len - 1] = c;
            else {
                sign_flag = 1;
                char s[3] = {' ', c, '\0'};
                string_add(str, s);
                if(c == '-' && !is_num(str->vol[str->len - 3]) && str->vol[str->len - 3] != ')') isNeg = 1;
            }
            lcd_lineclear(&lcd, 7, 0, 14);
            lcd.print(c);
            lcd_lineclear(&lcd, 0, 1, 15);
            x = vaNum = 0;
        }
        else if(is_func(c) && sign_flag) {//FUNC
            char s[3] = {' ', c, '\0'};
            string_add(str, s);
            lcd_lineclear(&lcd, 7, 0, 14);
            if(c == 's') lcd.print("sin");
            if(c == 'c') lcd.print("cos");
            if(c == 'l') lcd.print("ln");
            lcd.print("(");
            lcd_lineclear(&lcd, 0, 1, 15);
            x = 0;
            ykh_flag++;
        }
        else if(c == ')' && !sign_flag && ykh_flag) {
            string_add(str, " )");
            ykh_flag--;
            lcd_lineclear(&lcd, 7, 0, 14);
            lcd_lineclear(&lcd, 0, 1, 15);
            x = 0;
        }
        else if((c == 'e' || c == 'p') && sign_flag) {
            sign_flag = 0;
            x++;
            lcd.print(c);
            char s[12];
            strcpy(s, c == 'p' ? " 3.1415926" : " 2.71828182");
            string_add(str, s);
        }
        else if(c == '=' && !shift_flag) {
            if(ykh_flag) {
                lcd_lineclear(&lcd, 0, 0, 15);
                lcd.print("() not matches!");
            }
            else {
                lcd_lineclear(&lcd, 7, 0, 14);
                lcd_lineclear(&lcd, 0, 1, 15);
                double res = tree_calc(string_cstr(str));
                lcd.print(res);
                Serial.println(res);
            }
            reset_flag = 1;
        }
        else if(results.value == 0xFDB04F && shift_flag) {
            string_clear(str);
            calc_init();
        }
        Serial.println(string_cstr(str));
        irrecv.resume();// 恢复接收下一个红外遥控信号 防止空间中红外的反射误判
    }
    else if(reset_flag) {
        if(irrecv.decode(&results)) {
            Serial.println(results.value, HEX);
            if (results.value == 0xFD708F) {
                shift_flag = !shift_flag;//shift开关
                lcd.setCursor(15, 0);
                lcd.print(shift_flag ? "^" : " ");
            }
            if(results.value == 0xFDB04F && shift_flag) {
                string_clear(str);
                calc_init();
            }
            irrecv.resume();
        }
    }
}