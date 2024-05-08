// Note Generator Sketch from diyelectromusic
// https://diyelectromusic.wordpress.com/2023/01/05/arduino-make-your-uno-synth/
// Uses a defined series notes when "sliding" through the scale
// In this version, I removed many of the low and high notes from the defined 
// list of frequencies to make it easier to "select" notes with the potentiometer
// Lori Pfahler
// March 2024

int potPin = A0;
int SPEAKER = 9;

// Frequences for each note are taken from toneMelody
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

// Provide a list of the notes we want to be able play
int notes[] = {
 NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,
 NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
 NOTE_C5, 
};

void setup() {
  // added this to allow printing of pitch to serial plotter
  Serial.begin(9600);
}

void loop() {

  // This is a programming trick to work out the number of notes we've listed
  // The sizeof() operator returns the number of bytes in a variable type
  int numNotes = sizeof(notes)/sizeof(notes[0]);

  // Take the reading
  int potReading = analogRead(potPin);

  // if the reading is zero, turn it off
  if (potReading == 0) {
    noTone(SPEAKER);
  } 
  else {
    // This is a special function that will take one range of values,
    // in this case the analogue input reading between 0 and 1023, and
    // produce an equivalent point in another range of numbers, in this
    // case choose one of the notes in our list.
    int pitch = map(potReading, 0, 1023, 0, numNotes-1);
  
    tone(SPEAKER, notes[pitch]);
    Serial.println(notes[pitch]);
  }
  delay(1);  // as recommended by toneFollower
}
