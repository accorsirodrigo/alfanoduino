/*
   DuinoFano V1.0
   Projeto para Arduino Nano/Uno, replicando alguns funcionamentos dos paineis de bordo para Kart.
   Funcionalidades:
   Monitoramento de voltas, por meio de um botão (Melhor volta, ultima volta e volta atual);
   Velocidade (adquirida pelo GPS);
   Temperatura, pelo modulo MAX6675 e sensor tipo K;
   Display LCD 20x4;
   Em desenvolvimento:
   RPM;
*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>

#include "lcd/BigLcd.h"
#include "LapController.ino"
#include "domain/GPS.h"
#include "domain/CustomLCD.h"

static const String INVALID = "INVALID";
static const int INTERVAL = 3000;

int RXPin = 15;
int TXPin = 14;

int GPSBaud = 9600;
int turns = 0;
long millisInterval = millis();
long millisTurn = millis();
long millisControll = millis();

// lap
long initVal = millis();
long currentLap = 0;
double lapTime = 0.0;
int lapTimeDisplay = 3; // 3s
long lapMillis = 0;
double bestLap = 0.0;
double lastLap = 0.0;
boolean firstLap = true;

//LiquidCrystal_I2C m_lcd(0x3f, 20, 4);

CustomLCD lcd(0x3f, 20, 4);

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

GPS g1;

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  
  lcd.init();

  Timer1.initialize(1000);
  Timer1.attachInterrupt(incrementCurrentLap);

  pinMode(0, INPUT);
  pinMode(7, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(7), lapInterupt, FALLING);
  // attachInterrupt(digitalPinToInterrupt(0), lapInterupt, RISING);

  //lcd.welcomeScreen();
  // delay(3000);
  loadChars(lcd.getLcd());

  lcd.initLcdLayout();
}

void loop()
{
  lapTimmer();
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("Sinal GPS não detectado");
    while (true)
      ;
  }
}

void displayInfo()
{
  lapTimmer();
  // print speed
  Serial.print(F("Speed: "));
  String gpsSpeed = "0";
  if (gps.speed.isValid() && gps.speed.kmph() >= 1)
  {
    gpsSpeed = gps.speed.kmph();
  }
  Serial.print(gpsSpeed);
  printNumberDisplay(gpsSpeed);

  // print sattelites
  Serial.print(F(" |Sat: "));
  String sat = INVALID;
  if (gps.satellites.isValid())
  {
    sat = gps.satellites.value();
    Serial.print(gps.satellites.value());
  }
  else
    Serial.print(sat);
  lcd.printDisplay(12, 3, "GPS:" + sat, 8);
  Serial.println();
  delay(1);
}

// void displayInfo()
// {
//   if (gps.location.isValid())
//   {
//     g1.set(gps.location.lat(), gps.location.lng());

//     Serial.print("Latitude: ");
//     Serial.println(g1.getLat(), 6);
//     Serial.print("Longitude: ");
//     Serial.println(g1.getLng(), 6);
//   }
//   else
//   {
//     Serial.println("Não detectamos a localização");
//   }

//   Serial.print("Data: ");
//   if (gps.date.isValid())
//   {
//     Serial.print(gps.date.day());
//     Serial.print("/");
//     Serial.print(gps.date.month());
//     Serial.print("/");
//     Serial.println(gps.date.year());
//   }
//   else
//   {
//     Serial.println("Erro");
//   }

//   Serial.print("Time: ");
//   if (gps.time.isValid())
//   {
//     if (gps.time.hour() < 10)
//       Serial.print(F("0"));
//     Serial.print(gps.time.hour() - 3);
//     Serial.print(":");
//     if (gps.time.minute() < 10)
//       Serial.print(F("0"));
//     Serial.print(gps.time.minute());
//     Serial.print(":");
//     if (gps.time.second() < 10)
//       Serial.print(F("0"));
//     Serial.println(gps.time.second());
//   }
//   else
//   {
//     Serial.println("Não detectamos o horário atual");
//   }

//   Serial.print("Altitude: ");
//   Serial.println(gps.altitude.meters());

//   Serial.print("Speed: ");
//   Serial.println(gps.speed.kmph());

//   Serial.print("Sat: ");
//   Serial.println(gps.satellites.value());

//   Serial.println();
//   Serial.print("M_Time: ");
//   Serial.print((millis() - millisTurn) / 1000);
//   Serial.print(":");
//   Serial.println((millis() - millisTurn) % 1000);

//   Serial.print("Turns:");
//   Serial.println(turns);

//   delay(100);
// }

void lapCount()
{
  millisInterval = millis();
  if ((millis() - millisTurn) > 3000)
  {
    millisTurn = millis();
    turns++;
  }
}

void incrementCurrentLap(void)
{
  currentLap++;
}

void lapInterupt()
{

  if ((millis() - millisInterval) >= INTERVAL)
  {
    lapCount();
    millisInterval = millis();
    lapMillis = currentLap;
    Serial.println("INTERRUPT");
    if (firstLap)
    {
      currentLap = 0;
      firstLap = !firstLap;
    }
    else if (lapMillis > 1000)
    {
      lapTime = lapMillis / 1000.0;
      Serial.print("lap: ");
      Serial.print(lapTime);
      Serial.println("");
      if (lapTime < bestLap || bestLap == 0.0)
      {
        bestLap = lapTime;
      }
    }
    currentLap = 0;
    initVal = millis();
  }
}

void lapTimmer()
{
  if ((millis() - millisControll) < 10)
    return;
  millisControll = millis();
  if (millis() - initVal > 240000)
  {
    lapMillis = 0;
    firstLap = true;
  }

  if (!firstLap)
  {
    lcd.printDisplay(4, 2, String(currentLap / 1000.0), 6);
    lcd.printDisplay(12, 2, "#" + String(lapTime), 7);
    lcd.printDisplay(4, 3, String(bestLap), 6);
  }
}

void printNumberDisplay(String val)
{
  printNumber(lcd.getLcd(), val.toInt());
}