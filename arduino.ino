#include <OneWire.h>
#include <DallasTemperature.h>

#define MIN_TEMP 30.0
#define MAX_TEMP 60.0

int potPin = 2;    // select the input pin for the potentiometer

int fanPulse = 2;

int sleep_ms = 5000;

// DS18S20 Temperature chip i/o
OneWire ds(10);  // on pin 10

DallasTemperature tmp(&ds);

void setup(void) {  
  Serial.begin(9600);

  tmp.begin();

  pinMode(fanPulse, INPUT);
  digitalWrite(fanPulse, HIGH);
}

void loop(void) {
  tmp.requestTemperatures();
  double temp = tmp.getTempCByIndex(0);
  Serial.print("Temperature:    ");
  Serial.println(temp);

  //int val = analogRead(potPin) / 4;    // read the value from the sensor
  int val;
  if(temp < MIN_TEMP)
    val = 0;
  else if(temp > MAX_TEMP)
    val = 255;
  else
    val = (int)(((temp - (double)MIN_TEMP) / ((double)MAX_TEMP-(double)MIN_TEMP)) * 255.0);
  
  Serial.print("Analog Write:   ");
  analogWrite(3, val);
  analogWrite(9, max(116, val));
  Serial.println(val);
  delay(sleep_ms);
  readPulse();
}

void readPulse() {
  double pulseDuration = (double)(pulseIn(fanPulse, LOW) * 1E-3); // ms
  double frequency = 1.0E3 / pulseDuration;

  Serial.print("Pulse Duration: ");
  Serial.println(pulseDuration);
  Serial.print("Freq. (Hz):     ");
  Serial.println(frequency / 2);
  Serial.print("RPM:            ");
  Serial.println(frequency / 2 * 60);
  Serial.println("====================================");

}
