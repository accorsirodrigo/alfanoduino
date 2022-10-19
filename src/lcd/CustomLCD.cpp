#include "CustomLCD.h"
#include "BigLcd.h"

CustomLCD::CustomLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_row)
{
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_row;
}

void CustomLCD::init()
{
    lcd = LiquidCrystal_I2C(_Addr, _cols, _rows);
    lcd.init();
    lcd.backlight();

    welcomeScreen();
    delay(1000);
    loadChars(lcd);
    initLcdLayout();
}

void CustomLCD::printDisplay(int x, int y, String txt, int size)
{
    while (txt.length() < size)
    {
        txt.concat(" ");
    }
    if (txt.length() > size)
        txt = txt.substring(0, size);

    lcd.setCursor(x, y);
    lcd.print(txt);
}

void CustomLCD::welcomeScreen()
{
    printDisplay(0, 0, "###################", 20);
    printDisplay(6, 1, "DuinoFano", 20);
    printDisplay(4, 2, "Version 0.5.1", 20);
    printDisplay(6, 3, "Kart GPS", 20);
}

void CustomLCD::initLcdLayout()
{
    lcd.noBacklight();
    lcd.clear();
    delay(500);
    String lap = "LAP:";
    String bst = "BST:";
    String laps = "LAPs:";
    printDisplay(12, 0, laps, laps.length());
    printDisplay(0, 2, lap, lap.length());
    printDisplay(0, 3, bst, bst.length());
    lcd.backlight();
}

LiquidCrystal_I2C &CustomLCD::getLcd()
{
    return lcd;
}

void CustomLCD::printSpeed(String value)
{
    printNumber(lcd, value.toInt());
}
void CustomLCD::printGPS(String value)
{
    printDisplay(12, 3, "GPS:" + value, 8);
}
void CustomLCD::printTime(String value)
{
    printDisplay(4, 2, value, 6);
}
void CustomLCD::printBestTime(String value)
{
    printDisplay(4, 3, value, 6);
}

void CustomLCD::printLastLap(String value)
{
    printDisplay(12, 2, "#" + value, 7);
}

void CustomLCD::printLaps(String value)
{
    printDisplay(17, 0, value, value.length());
}