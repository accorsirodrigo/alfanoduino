#ifndef CustomLCD_H
#define CustomLCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class CustomLCD {
    private:
        uint8_t _Addr;
        uint8_t _cols;
        uint8_t _rows;
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(_Addr, _cols, _rows);
    public:
        CustomLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
        void init();
        void printDisplay(int x, int y, String txt, int size);
        void welcomeScreen();
        void initLcdLayout();
        LiquidCrystal_I2C& getLcd();
};

#endif