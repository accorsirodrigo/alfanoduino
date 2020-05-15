#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "BigLcd.h"

LiquidCrystal_I2C m_lcd(0x3F, 20, 4);

void setup()
{
    Serial.begin(9600);
    m_lcd.init(); // initialize the lcd
    // Print a message to the LCD.
    m_lcd.backlight();
    loadChars(m_lcd);
    //print("Rodrigo", 0,0);
    Serial.println("Inicializado");
}

void loop()
{
    Serial.println("Ok 2");
    printNumber(m_lcd, 112);
    delay(2000);
}

void print(String txt, int x, int y)
{
    m_lcd.setCursor(x, y);
    m_lcd.print(txt);
}
