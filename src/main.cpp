/**
 * Energy Monitoring System
 * 
 * Monitor energy consumption in your home.
 */

#include <Arduino.h>
#include "EmonLib.h"

EnergyMonitor emon1;

double Vrms = 16.0;  // Input voltage.
double Ical = 60.6;  // Current calibration.
int Nsamples = 1480;  // Number of calibration samples.
int InputPin = 1;     // Arduino input pin.

void setup() {
  Serial.begin(9600);

  emon1.current(InputPin, Ical);  // Current: input pin, calibration.
}

void loop() {
  double Irms = emon1.calcIrms(Nsamples); // Calculate Irms only.

  Serial.print("Voltage: ");
  Serial.println(Vrms);                   // Input voltage (Vrms).
  Serial.print("Current: ");
  Serial.println(Irms);                   // Current reading (Irms).
  Serial.print("Apparent Power: ");
  Serial.println(Irms * Vrms);            // Apparent power.
}