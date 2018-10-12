const int button = 7;       //The push button is on pin 7
const int led =  3;         //The LED is on PWM pin 3
const int annoyingLight = 13; //This is just to turn off the built in LED

int pushState = 0;           //These two variables keep track of the button pushes
int prevPushState;
int pushStateCount = 0;      //This is used to iterate between LED states

const long blinkTime = 250;         //These three variables are used for LED blinking  
unsigned long previousTime = 0;       
int ledBlinkState = LOW;

void setup() {
  //Initialize pins. led pin is an output, button pin is an input, I'm turning off the annoying LED
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(annoyingLight, OUTPUT);
  digitalWrite(annoyingLight, LOW);

}

void loop() {
  //Keep track of the previous state of the button. Records when the button is released. Add 1 to the counter for every button push
  prevPushState = pushState;
  pushState = digitalRead(button);
  if (prevPushState > pushState) {
    pushStateCount++;
  }
  //Use mod division to keep track of which state. 0 = led off, 1 = bright, 2 = intermediate, 3 = dim, 4 = blinking
  if (pushStateCount % 5 == 0) {
    analogWrite(led, 0); //Off
  }
  if (pushStateCount % 5 == 1) {
    brightest();
  }
  if (pushStateCount % 5 == 2) {
    intermediate();
  }
  if (pushStateCount % 5 == 3) {
    dimmest();
  }
  if (pushStateCount % 5 == 4) {
    flashing();
  }
}

void brightest() {
  while (pushState == 0) {
    analogWrite(led, 255);  //Brightest. AnalogWrite has built in PWM
    pushState = digitalRead(button); //This is used to break out of the while loop and back into the main loop
  }
}

void intermediate() {
  while (pushState == 0) {
    analogWrite(led, 75);  //Intermediate
    pushState = digitalRead(button);
  }
}

void dimmest() {
  while (pushState == 0) {
    analogWrite(led, 10);  //least bright
    pushState = digitalRead(button);
  }
}

void flashing() {
  while (pushState == 0) {
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
      digitalWrite(led, ledBlinkState);
    }
    pushState = digitalRead(button);
  }
}
