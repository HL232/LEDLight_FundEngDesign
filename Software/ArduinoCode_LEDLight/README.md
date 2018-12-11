## How my software code runs:

Basically: 

The push button that sets the LED is on Pin 8. If you push the button it increases the count by 1. The count is mod_divided to determine the state of the LED. AnalogWrite on pin 9 is used to set the state of the LED. Pin 9 has built in PWM allowing for different brightness settings. The blinking 2Hz light is just based on time values

The push button that plays the music is Pin 12. When you push it, it triggers output on Pin 11. It triggers the music to play, which I manually coded the pitch values and the note length durations. However, while the music is playing, nothing else can happen.

Debouce buttons also occcurs in software. Basically, it is a time based debounce that only allows one "button press" every 50ms.

More details are written as comments in the code itself (including references to appropriate code sources)

## Future improvements
The biggest improvement I want to implement is changing the music. I could not use an interrupt to stop the music, probably because of the microDelays that are required to play the music. Nothing can happen during these delays (and there are a LOT of delays because it's a long song). 

I would like to be able to change the LED state while the music is playing as well. This would interweaving the music and LED light code, which are separate and modular for  now. 

