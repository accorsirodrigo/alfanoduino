#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "BigChars.h"

LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
    Serial.begin(9600);
    lcd.init(); // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();
    //print("Rodrigo", 0,0);
    Serial.println("Inicializado");
}

void loop()
{
    Serial.println("Ok 2");
    delay(2000);
}

void print(String txt, int x, int y)
{
    lcd.setCursor(x, y);
    lcd.print(txt);
}