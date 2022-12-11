#include"calculator.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>
LiquidCrystal_I2C lcd(0x20, 16, 2);
int IR_RECEIVE_PIN = 11;
int x, y;
bool shift_flag, ykh_flag;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (IrReceiver.decode())
    {
        uint32_t value = IrReceiver.decodedIRData.decodedRawData;
        if(value == 0xF30CBF00)//按0
        {
            Tree* tr = (Tree *)malloc(sizeof(Tree));
            tree_init(tr, "1 + 2 * 3 - 4 + 6 ^ 2 / 2 ^ 2 - 1");
            Serial.println(get_value(tr));
            tree_del(tr);
            free(tr);
        }
        IrReceiver.resume();
    }
}
