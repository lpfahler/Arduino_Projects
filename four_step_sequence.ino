/*
Four Step Sequencer Sketch 
from diyelectromusic
https://diyelectromusic.wordpress.com/2023/01/05/arduino-make-your-uno-synth/
Uses a defined series notes when "sliding" through the scale
Lori Pfahler
March 2024
*/

#define NUM_POTS 4
int potPins[NUM_POTS] = {A0, A2, A1, A3};
int tempoPin = A4;
int SPEAKER = 9;
#define MIN_POT_READING 4 // Value for the lowest note

#define TEMPO_MIN 30  // 1 every two seconds
#define TEMPO_MAX 480 // 8 a second

// Frequences for each note are taken from toneMelody
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
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
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Provide a list of the notes we want to be able play
// I reduced the array of notes available to make it easier to select
// specific notes
int notes[] = {
 NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,
 NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
 NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5
};

int numNotes;
int playingNote;

void setup() {
  // This is a programming trick to work out the number of notes we've listed
  numNotes = sizeof(notes)/sizeof(notes[0]);

  playingNote = 0;
}

void loop() {
  // Check the tempo
  int tempo = map(analogRead(tempoPin), 0, 1023, TEMPO_MIN, TEMPO_MAX);

  if (playingNote >= NUM_POTS) {
    playingNote = 0;
  }

  // Take the reading for this pot
  int potReading = analogRead(potPins[playingNote]);

  // if the reading is zero (or almost zero) turn off any notes
  if (potReading < MIN_POT_READING) {
    noTone(SPEAKER);
  } else {
    // This is a special function that will take one range of values,
    // in this case the analogue input reading between 0 and 1023, and
    // produce an equivalent point in another range of numbers, in this
    // case choose one of the notes in our list.
    int noteIdx = map(potReading, MIN_POT_READING, 1023, 0, numNotes-1);
    tone(SPEAKER, notes[noteIdx]);
  }

  // The tempo is in beats per minute (bpm).
  // So beats per second = tempo/60
  // So the time in seconds of each beat = 1/beats per second
  // So time in mS = 1000 / (tempo/60)
  // or time in mS = 60000 / tempo
  delay(60000/tempo);
  playingNote++;
}