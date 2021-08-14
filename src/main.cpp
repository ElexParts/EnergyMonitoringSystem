/**
 * Energy Monitoring System
 * 
 * Monitor energy consumption in your home.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "EmonLib.h"

// Define constants.
#define DEBUG 0 // Enable or disable debugging

// Configure Energy Monitor.
EnergyMonitor emon1;

double Vrms         = 220.0;  // Input voltage.
double Ical         = 60.6;   // Current calibration.
int Nsamples        = 1480;   // Number of calibration samples.
int EnergySensorPin = 1;      // Arduino input pin.

double Irms = 0.0;  // Current reading.
double P    = 0.0;  // Calculated power.

// Configure LCD display.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Set reading interval.
unsigned long previousMillis = 0;     // Previous time.
const long interval          = 1000;  // 1 second reading interval.

void setup() {
  if (DEBUG) {
    // Setup serial monitor.
    Serial.begin(9600);
  }

  // Initialize a 16x2 LCD display.
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Setup energy monitor.
  emon1.current(EnergySensorPin, Ical);  // Current: input pin, calibration.

  // Clear LCD display after 3 seconds.
  delay(3000);
  lcd.clear();
}

void loop() {
  // Current time.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time.
    previousMillis = currentMillis;

    // Get energy consumption.
    Irms = emon1.calcIrms(Nsamples);
    P = Irms * Vrms;

    // Display debug message to serial monitor.
    if (DEBUG) {
      Serial.print("Voltage(V): ");
      Serial.println(Vrms);
      Serial.print("Current(I): ");
      Serial.println(Irms);
      Serial.print("Power(W): ");
      Serial.println(P);
    }
  }

  // Display energy consumption.
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.setCursor(2, 0);
  lcd.print(Vrms);

  lcd.setCursor(8, 0);
  lcd.print("I:");
  lcd.setCursor(10, 0);
  lcd.print(Irms);

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.setCursor(2, 1);
  lcd.print(P);
}