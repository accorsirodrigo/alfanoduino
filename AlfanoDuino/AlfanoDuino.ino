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
#include <max6675.h>
#include <TimerOne.h>
#include "BigLcd.h"
#include "LCDFun.h"

#define rpmPin 2
#define lapPin 3

#define lines 4
#define columns 20

#define ktcSO 8
#define ktcCS 9
#define ktcCLK 10

#define TXPin 13
#define RXPin 12

#define systemBaud 9600
#define GPSBaud 9600

LiquidCrystal_I2C m_lcd(0x3F, columns, lines);
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

static const String INVALID = "INVALID";

//RPM
long rpmMillis = millis();
int countRpm = 0;

//lap
long initVal = millis();
long currentLap = 0;
double lapTime = 0.0;
int lapTimeDisplay = 3; //3s
long lapMillis = 0;
double bestLap = 0.0;
double lastLap = 0.0;
boolean firstLap = true;


void setup() {
  Serial.begin(systemBaud);
  ss.begin(GPSBaud);
  Serial.print("TinyGPS++ library v. "); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();

  Timer1.initialize(1000);
  Timer1.attachInterrupt(incrementCurrentLap); 

  m_lcd.init(); // initialize the lcd
  m_lcd.backlight();

  welcomeScreen(m_lcd);
  delay(3000);

  loadChars(m_lcd);

  pinMode(lapPin, INPUT);
  pinMode(rpmPin, INPUT);
  digitalWrite(lapPin, LOW);
  digitalWrite(rpmPin, LOW);

  attachInterrupt(digitalPinToInterrupt(lapPin), lapInterupt, HIGH);
  attachInterrupt(digitalPinToInterrupt(rpmPin), rpmInterrupt, HIGH);

  initLcdLayout(m_lcd);

}

void loop() {
  lapTimmer();
  printTmp();
  //printRpm();
  while (ss.available() > 0) {
    lapTimmer();
    printTmp();
    //printRpm();
    //delay(200);
    if (gps.encode(ss.read())) {
      displayInfo();
    }
  }
}

void printTmp() {
  //printDisplay(16, 1, String(ktc.readCelsius()), 4, m_lcd);
}

void lapInterupt() {
  //lapMillis = millis() - initVal;
  //lapMillis = currentLap;
  if (firstLap) {
    currentLap = 0;
    firstLap = !firstLap;
  } else if (lapMillis > 1000) {
    lapTime = lapMillis / 1000.0;
    Serial.print("lap: "); Serial.print(lapTime);
    Serial.println("");
    if (lapTime < bestLap || bestLap == 0.0) {
      bestLap = lapTime;
    }
  }
  currentLap = 0;
  initVal = millis();
}

void incrementCurrentLap(void) {
  currentLap++;
  lapTimmer();
}

void rpmInterrupt() {
  if ((millis() - rpmMillis) > 2) {
    countRpm++;
    printRpm();
  }
}

double rpm;
int countRefer;
void printRpm() {
  if (countRpm > 5) {
    countRefer = countRpm;
    rpm = (60000) / ((millis() - rpmMillis) / countRefer);

    Serial.println(rpm);

    rpmMillis = millis();
    countRpm = 0;
    //printDisplay(4, 1, String(rpm), 4);
  }
}

void lapTimmer() {
  if (millis() - initVal > 240000) {
    lapMillis = 0;
    firstLap = true;
  }

  if (!firstLap) {
    //double currentLap = (millis() - initVal) / 1000.0;
    printDisplay(4, 2, String(currentLap / 1000.0), 6, m_lcd);
    printDisplay(12, 2, "#" + String(lapTime), 7, m_lcd);
    printDisplay(4, 3, String(bestLap), 6, m_lcd);
  }
}

void displayInfo() {
  //print speed
  Serial.print(F("Speed: "));
  String gpsSpeed = "0";
  if (gps.speed.isValid() && gps.speed.kmph() >= 1) {
    gpsSpeed = gps.speed.kmph();
  }
  Serial.print(gpsSpeed);
  printNumberDisplay(gpsSpeed);

  //print sattelites
  Serial.print(F(" |Sat: "));
  String sat = INVALID;
  if (gps.satellites.isValid()) {
    sat = gps.satellites.value();
    Serial.print(gps.satellites.value());
  } else
    Serial.print(sat);
  printDisplay(12, 3, "GPS:" + sat, 8, m_lcd);
  Serial.println();
}

void printNumberDisplay(String val) {
  printNumber(m_lcd, val.toInt());
}
