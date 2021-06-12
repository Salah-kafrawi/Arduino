// Force indicator, LED lights
// Taibah Valley Summer Training 
int forceApplied = A0; // Force sensor is connected to analog 0
int Green = 11;  // connect Green LED to pin 11 (PWM pin)
int Red = 10; // Connect Red LED to pin 10 ( PWM pin)
int forceReading;  // the analog reading from the Force resistor divider
int LEDup; // Used with the green light
int LEDdown; // Used with the Red light
void setup(void) {
  Serial.begin(9600);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);  
}
void loop(void) {
  forceReading = analogRead(forceApplied);
  Serial.print("The applied force is = ");
  Serial.println(forceReading);
// Lights Mapping, Green is proportional with the applied force
// Lights Mapping, Red is inversely proportional with the applied force 
  LEDup = map(forceReading, 0, 1023, 0, 255);
  LEDdown=map(forceReading,0,1023,255,0);
  analogWrite(Green, LEDup);
  analogWrite(Red, LEDdown);
  delay(100);
}
