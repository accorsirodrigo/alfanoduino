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

        void welcomeScreen();
        void initLcdLayout();
        void printDisplay(int x, int y, String txt, int size);
        LiquidCrystal_I2C& getLcd();
    public:
        CustomLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
        void init();
        void printSpeed(String value);
        void printGPS(String value);
        void printTime(String value);
        void printBestTime(String value);
        void printLastLap(String value);
        void printLaps(String value);
};

#endif