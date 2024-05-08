/* 
Code originally from 
https://www.hackster.io/eEdizon/arduino-step-sequencer-afea0e
Licensed under © GPL3+

Code for Testing Synth Sheild - Make Your Uno Kit
The LED code is not needed and was removed
Revised and additional comments added by 
Lori Pfahler
March 2024

Notes:
  tone(pin, frequency, duration)
  Generates a square wave of the specified frequency (and 50% duty cycle) 
  on a pin. A duration can be specified, otherwise the wave continues 
  until a call to noTone(). The pin can be connected to a piezo buzzer
  or other speaker to play tones
*/

const byte speaker = 9;  // Speaker pin
bool debug = false;      // Used to print values to Serial Monitor
long counter = 0;        // Used for speed
long tempo;              // Used for reading the speed from potentiometer
int lowFreq = 10;        // The lower frequency boundary
int highFreq = 2000;     // The higher frequency boundary
int pattern = 0;         // Current potentiometer
unsigned int note;       // Note that will be played

//  funtion to get the notes from potentiometers
int getNote(int pattern) {  
  if (pattern == 0) {
    note = map(analogRead(A0), 0, 1023, lowFreq, highFreq);
  } 
  else if (pattern == 1) {
    note = map(analogRead(A1), 0, 1023, lowFreq, highFreq);
  } 
  else if (pattern == 2) {
    note = map(analogRead(A2), 0, 1023, lowFreq, highFreq);
  } 
  else if (pattern == 3) {
    note = map(analogRead(A3), 0, 1023, lowFreq, highFreq);
  }
  return note;
}

// nothing needed in setup without LEDs involved
void setup() {
}

void loop() {
  // get tempo from potentiometer connected to A4
  tempo = map(analogRead(A4), 0, 1023, 4000, 100);

  // If speed is less than 3900 - get notes from all four potentiometers
  // Unless the potentiometer is set to below the lowFreq
  if (tempo < 3900) { 
    if (counter > tempo) {
      // print for debugging
      if (debug) {
        Serial.println(pattern);
      }
      // turn tone off and reset counter
      noTone(speaker);
      counter = 0;

      // getNote for current Potentiometer (pattern)
      note = getNote(pattern);
      // advance through the four potentiometers
      pattern = (pattern + 1) % 4;
      // if the note is above the lowFreq + 10  - play the note
      if (note > lowFreq + 10) {
        tone(speaker, note);
      }
    }

    // advance the counter - this functions as a delay (?)
    // to control the speed of the notes playing. If the tempo is set low 
    // it will take longer to change the notes since we 
    // have to add more to the counter to advance
    counter++;


  } 
  // if the tempo is above 3900 that means we are
  // "stopped" using only one potentiometer 
  // and playing just one note in the sequence
  else { 
    // get the single note from the appropriate potentiometer 
    unsigned int note = map(analogRead(pattern), 0, 1023, lowFreq, highFreq);

    if (note > lowFreq + 10) {
      tone(speaker, note);
    }
    else {
      // note is below lowFreq +10 and no tone will be played
      noTone(speaker);
    }
  }
}
