#define button_pin 12 //The push button is on pin 12
#define led_pin 9 //The LED is on PWM pin 9
#define blinkTime 250 //Blink time
#define annoyingLight 13 //This is just to turn off the built in LED

int pushState = 0;           //These two variables keep track of the button pushes
int prevPushState;
int pushStateCount = 0;      //This is used to iterate between LED states
int modSwitchState;

//These two variables keep track of LED blinking
unsigned long previousTime = 0;       
int ledBlinkState = LOW;

void setup() {
  //Initialize pins. led pin is an output, button pin is an input
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(annoyingLight, OUTPUT);
  //I'm turning off the annoying LED built into pin 13
  digitalWrite(annoyingLight, LOW);
  //Instead of using attachInterrupt(), I coded my own interrupt function
}

void loop() {
  button_push();
  set_LED_state();
}

void button_push(){
    //Keep track of the previous state of the button. Records when the button is released. Add 1 to the counter for every button push
  prevPushState = pushState;
  pushState = digitalRead(button_pin);
  if (prevPushState > pushState) {
    pushStateCount++;
  }
  modSwitchState = pushStateCount % 5;
}

void set_LED_state(){
    //Use mod division to keep track of which state. 0 = led off, 1 = bright, 2 = intermediate, 3 = dim, 4 = blinking
  switch (modSwitchState){
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
