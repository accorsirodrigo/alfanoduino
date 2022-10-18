#include "CustomLCD.h"

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
    printDisplay(0, 2, lap, lap.length());
    printDisplay(0, 3, bst, bst.length());
    lcd.backlight();
}

LiquidCrystal_I2C& CustomLCD::getLcd()
{
    return lcd;
}