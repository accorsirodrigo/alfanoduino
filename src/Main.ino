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

#include "domain/GPS.h"
#include "lcd/CustomLCD.h"
#include "lap/LapController.h"
#include "track/Track.h"

static const String INVALID = "INVALID";
static const int INTERVAL = 3000;
static const int GPS_BAUD = 9600;

int RXPin = 15;
int TXPin = 14;

long interruptIntervalMs = millis();
long displayUpdateIntervalMs = millis();

CustomLCD lcd(0x3f, 20, 4);
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

Track npt(-28.709403, -51.929740, 40.0);
//LAT=-28.709014|LNG=-51.929721

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(GPS_BAUD);

  lcd.init();

  pinMode(0, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(0, LOW);

  attachInterrupt(digitalPinToInterrupt(7), lapInterupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(0), lapInterupt, RISING);
}

void loop()
{
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("Sinal GPS não detectado");
    while (true)
      ;
  }

  lapTimmer();
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
}

void displayInfo()
{
  lapTimmer();
  gpsTurnControll();
  // print speed
  Serial.print(F("Speed: "));
  String gpsSpeed = "0";
  if (gps.speed.isValid() && gps.speed.kmph() >= 1)
  {
    gpsSpeed = gps.speed.kmph();
  }
  Serial.print(gpsSpeed);
  lcd.printSpeed(gpsSpeed);

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

  lcd.printGPS(sat);

  if (gps.location.isValid())
  {
    Serial.print("|LAT=");
    Serial.print(gps.location.lat(), 6);
    Serial.print("|LNG=");
    Serial.print(gps.location.lng(), 6);
  }

  Serial.println();
  delay(1);
}

void lapInterupt()
{
  if ((millis() - interruptIntervalMs) >= INTERVAL)
  {
    interruptIntervalMs = millis();
    if (LapCont.isFirstLap())
      LapCont.startLap();
    else
      LapCont.endLap();
  }
}

void lapTimmer()
{
  if ((millis() - displayUpdateIntervalMs) < 10)
    return;

  displayUpdateIntervalMs = millis();
  lcd.printTime(String(LapCont.getCurrentLapTime()));
  lcd.printLastLap(String(LapCont.lasLapTime()));
  lcd.printBestTime(String(LapCont.getBestLapTime()));
  lcd.printLaps(String(LapCont.getLaps()));
}

void gpsTurnControll()
{
  if (gps.location.isValid())
  {
    double distance = gps.distanceBetween(npt.getLat(), npt.getLng(), gps.location.lat(), gps.location.lng());
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance <= npt.getTolerance())
    {
      Serial.println("LAP");
      digitalWrite(0, HIGH);
      digitalWrite(0, LOW);
    }
  }
}