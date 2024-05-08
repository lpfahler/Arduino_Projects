/*
Simple DIY Electronic Music Projects
diyelectromusic.wordpress.com

Make Your Uno - 12 Tone Piano
https://diyelectromusic.wordpress.com/2023/01/05/arduino-make-your-uno-synth/

Lori Pfahler
April 2024
*/

// Pitches
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523


// Set up the input and output pins to be used for the speaker and keys.
#define SPEAKER  9
int keys[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13
};

// Get the number of keys - LBP moved code here
int numkeys = sizeof(keys)/sizeof(keys[0]);  

// Set the notes to be played by each key
int notes[] = {
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5
};

void setup() {
  // Initialize the input buttons as piano "keys"
  for (int k = 0; k < numkeys; k++) {
    pinMode (keys[k], INPUT_PULLUP);
  } 
}

void loop() {
  // Check each button and if pressed play the note.
  // If no buttons are pressed, turn off all notes.
  // Note - the last button to be checked will be
  // the note that ends up being played.
  int playing = -1;
  for (int k = 0; k < numkeys; k++) {
    int buttonState = digitalRead (keys[k]);
    if (buttonState == LOW) {
      playing = k;
    }
  }

  if (playing != -1) {
    tone (SPEAKER, notes[playing]);
  } else {
    // If we didn't find a button pressed, make sure everything is off
    noTone(SPEAKER);
  }
}