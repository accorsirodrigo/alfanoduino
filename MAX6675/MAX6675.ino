//https://www.circuitmagic.com/arduino/temperature-sensor-with-arduino-k-type-thermocouple-sensor-max6675-module/
#include <max6675.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include "BigChars.h"

int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;

LiquidCrystal_I2C lcd(0x3F, 20, 4);
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

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
    //Serial.println("Ok 2");
    Serial.print("Deg C = ");
    Serial.print(ktc.readCelsius());
    Serial.print("\t Deg F = ");
    Serial.println(ktc.readFahrenheit());
    print(String(ktc.readCelsius()), 15,0, 4);
    delay(500);
}

void print(String txt, int x, int y, int size)
{
    while(txt.length() < size){
        txt.concat(" ");
    }
    lcd.setCursor(x, y);
    lcd.print(txt);
}
