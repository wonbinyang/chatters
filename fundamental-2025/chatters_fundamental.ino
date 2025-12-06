// This sketch forms the fundamental code base
// of the "Chatters" series by Wonbin Yang.
// 
// Released under CC0 1.0 Universal.
// You may use it for any purpose, without restriction.
// Credit is appreciated but not required.
//
// — Wonbin Yang

// This creature makes little beeping sounds. Each beep wiggles
// up and down a bit, and the glow shows how high or low the beep is.

// Ports where the creature "speaks" and "glows"
#define VOICE_PIN 5   // where the beep comes out
#define GLOW_PIN 10   // where the light glows

// How high or low the beep can be (in Hz)
const int MIN_BEEP_PITCH = 800;
const int MAX_BEEP_PITCH = 2500;

// How short or long one beep can be (milliseconds)
const int MIN_BEEP_TIME = 50;
const int MAX_BEEP_TIME = 300;

// How short or long the whole pattern of beeps can last (milliseconds)
const int MIN_PATTERN_TIME = 100;
const int MAX_PATTERN_TIME = 3000;

// Little rests between beeps (milliseconds)
const int TIME_BETWEEN_BEEPS = 20;

// Rest between full patterns (milliseconds)
const int REST_TIME = 2000;

// Wiggle settings (vibrato-like shaking of the beep)
const int MIN_WIGGLE_SPEED = 5;     // how fast it wiggles
const int MAX_WIGGLE_SPEED = 30;

const int MIN_WIGGLE_AMOUNT = 10;   // how much it wiggles
const int MAX_WIGGLE_AMOUNT = 150;

void make_beep_pattern();  // function to create a full pattern

void setup() {
  pinMode(VOICE_PIN, OUTPUT);
  pinMode(GLOW_PIN, OUTPUT);
  randomSeed(analogRead(A0));  // randomness from analog noise
}

void loop() {
  make_beep_pattern();
  delay(REST_TIME);
}

// Make a pattern of small beeps
void make_beep_pattern() {
  long pattern_length = random(MIN_PATTERN_TIME, MAX_PATTERN_TIME + 1);
  long pattern_start = millis();

  while (millis() - pattern_start < pattern_length) {

    int beep_pitch = random(MIN_BEEP_PITCH, MAX_BEEP_PITCH + 1);  // pitch
    int beep_time  = random(MIN_BEEP_TIME, MAX_BEEP_TIME + 1);    // duration

    int wiggle_speed  = random(MIN_WIGGLE_SPEED, MAX_WIGGLE_SPEED + 1);
    int wiggle_amount = random(MIN_WIGGLE_AMOUNT, MAX_WIGGLE_AMOUNT + 1);

    int glow_strength = map(beep_pitch, MIN_BEEP_PITCH, MAX_BEEP_PITCH, 50, 255);
    glow_strength = constrain(glow_strength, 50, 255);

    long beep_start = millis();
    long last_wiggle = 0;
    bool wiggle_up = true;

    while (millis() - beep_start < beep_time) {
      if (millis() - last_wiggle >= wiggle_speed) {

        int now_pitch;
        if (wiggle_up) now_pitch = beep_pitch + wiggle_amount;
        else           now_pitch = beep_pitch - wiggle_amount;

        tone(VOICE_PIN, now_pitch);

        wiggle_up = !wiggle_up;
        last_wiggle = millis();
      }

      analogWrite(GLOW_PIN, glow_strength);
      delay(1);
    }

    noTone(VOICE_PIN);
    analogWrite(GLOW_PIN, 0);
    delay(TIME_BETWEEN_BEEPS);
  }

  noTone(VOICE_PIN);
  analogWrite(GLOW_PIN, 0);
}
      
