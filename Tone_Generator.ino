/* Tone Generator Sketch
from diyelectromusic
https://diyelectromusic.wordpress.com/2023/01/06/arduino-make-your-uno-synth-1-simple-tones/

Lori Pfahler
March 2024

NOTES:
Uses tone(pin, frequency, duration) 
generates a square wave at a specified frequency with a 50% Duty Cycle
duration is in ms
if no duration is given, it will continue to play until a noTone() is called
*/

int potPin = A0;
int SPEAKER = 9;

void setup() {
  // added this to allow printing of pitch to serial plotter
  Serial.begin(9600);
}

void loop() {
  int potReading = analogRead(potPin);

  if (potReading == 0) {
    // end tone playing when potentiometer is turned all the way done
    noTone(SPEAKER);
  } else {
    // map potReading to freq range of 120 to 1500
    int pitch = map(potReading, 0, 1023, 120, 1500);
    // added this to show pitch on serial plotter
    Serial.println(pitch);
    // send pitch to speaker pin
    tone(SPEAKER, pitch);
  }
}
