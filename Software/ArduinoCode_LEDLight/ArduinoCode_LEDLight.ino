//**********************************************************************************************************************************
//******************************************************************Stuff for LED***************************************************
//**********************************************************************************************************************************
#define button_pin 8 //The push button is on pin 8
#define led_pin 9 //The LED is on PWM pin 9
#define blinkTime 250 //Blink time
#define annoyingLight 13 //This is just to turn off the built in LED

int pushState = 0;           //These two variables keep track of the button pushes
int prevPushState = 0;
int realPushState;
int pushStateCount = 0;      //This is used to iterate between LED states
int modSwitchState;

//These two variables keep track of LED blinking
unsigned long previousTime = 0;
int ledBlinkState = LOW;

//These variables are used for debounce
//Code for button debounce modified from https://www.arduino.cc/en/Tutorial/Debounce
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void button_push() {
  //Keep track of the previous state of the button. Records when the button is released. Add 1 to the counter for every button push
  prevPushState = pushState;
  pushState = digitalRead(button_pin);
  if (pushState != prevPushState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (pushState != realPushState) {
      realPushState = pushState;
      if (realPushState == LOW) {
        pushStateCount++;
      }
    }
  }
  modSwitchState = pushStateCount % 5;
}

void set_LED_state() {
  //Use mod division to keep track of which state. 0 = led off, 1 = bright, 2 = intermediate, 3 = dim, 4 = blinking
  switch (modSwitchState) {
    case 0:
      analogWrite(led_pin, 0); //Off
      break;
    case 1:
      brightest();
      break;
    case 2:
      intermediate();
      break;
    case 3:
      dimmest();
      break;
    case 4:
      flashing();
      break;
  }
}

void brightest() {
  analogWrite(led_pin, 255);  //Brightest. AnalogWrite has built in PWM
}

void intermediate() {
  analogWrite(led_pin, 75);  //Intermediate
}

void dimmest() {
  analogWrite(led_pin, 10);  //least bright
}

void flashing() {
  //This blinking code was based on https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
  //Basically, it keeps track of every 250ms interval and changes the LED from on to off or vice versa
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= blinkTime) {
    previousTime = currentTime;
    if (ledBlinkState == LOW) {
      ledBlinkState = HIGH;
    } else {
      ledBlinkState = LOW;
    }
    digitalWrite(led_pin, ledBlinkState);
  }
}
//**********************************************************************************************************************************
//******************************************************************Stuff for Music*************************************************
//**********************************************************************************************************************************
// Music code based on : https://www.arduino.cc/en/Tutorial/PlayMelody
// TONES  ==========================================
// Start by defining the relationship between
//       note, period, &  frequency.
#define  D4     3400    // 294 Hz 
#define  E     3038    // 329 Hz 
#define  F     2864    // 349 Hz 
#define  G     2550    // 392 Hz 
#define  A     2272    // 440 Hz 
#define  B     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
#define D5     1703

// DURATION OF THE NOTES
#define BPM 200    //  you can change this value changing all the others
#define h 2*q //half 2/4
#define q 6000/BPM //quarter 1/4 
#define e q/2   //eighth 1/8
#define w 4*q // whole 4/4
#define d 3*q //dotted half


// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
#define speakerOut 11 //The speaker output is on pin 11
#define button_pin_music 12 //The push button is on pin 12

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = {
  G, A, G, E, C,
  A, G,
  G, A, G, A, G, C,
  B,
  F, G, F, D4, B,
  A, G,
  G, A, G, A, G, A,
  E,
  //Measure 9
  G, A, G, E, C,
  A, G,
  G, A, G, A, G, C,
  B,
  F, G, F, D4, B,
  A, G,
  G, A, G, A, G, A,
  E,
  //Measure 17
  A, A, C, A,
  G, E, G,
  F, A, G, F,
  E,
  D4, E, G, A,
  B, B, B,
  D5, C, B, A,
  G, F, D4,
  //Measure 25
  G, A, G, E, C,
  A, G,
  G, A, G, A, G, C,
  B,
  F, G, F, D4, B,
  A, G,
  G, A, G, A, G, D5,
  C
};
int beats[]  = {   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
                   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
                   //Measure 9
                   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
                   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
                   //Measure 17
                   q, q, q, q,
                   q, q, h,
                   q, q, q, q,
                   w,
                   q, q, q, q,
                   q, q, h,
                   q, q, q, q,
                   q, q, h,
                   //Measure 25
                   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
                   e, q, e, q, q,
                   q, d,
                   e, e, e, e, q, q,
                   w,
               };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 500;
// Loop variable to increase Rest length
int rest_count = 100;

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

//These variables keep track of the button pushes
int pushState_music = 0;
int prevPushState_music = 0;
int realPushState_music;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
}

void play_music() {
  prevPushState_music = pushState_music;
  pushState_music = digitalRead(button_pin_music);
  if (pushState_music != prevPushState_music) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (pushState_music != realPushState_music) {
      realPushState_music = pushState_music;
      if (realPushState_music == LOW) {
        for (int i = 0; i < MAX_COUNT; i++) {
          tone_ = melody[i];
          beat = beats[i];
          duration = beat * tempo; // Set up timing
          playTone();
          // A pause between notes...
          delayMicroseconds(pause);
        }
      }
    }
  }
}

//**********************************************************************************************************************************
//******************************************************************SETUP AND LOOP**************************************************
//**********************************************************************************************************************************
void setup() {
  //Initialize pins. led pin is an output, button pin is an input
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(annoyingLight, OUTPUT);
  //I'm turning off the annoying LED built into pin 13
  digitalWrite(annoyingLight, LOW);
  pinMode(button_pin_music, INPUT);
  pinMode(speakerOut, OUTPUT);
}

void loop() {
  button_push();
  set_LED_state();
  play_music();
}
