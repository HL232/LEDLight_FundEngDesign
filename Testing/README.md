This folder contains video demos of the various versions of my device. A few of the videos are too large to upload directly to Github. Please these links to access the videos:

 Version 1.0: https://photos.app.goo.gl/UVKxtpJu6PFzeBne8
 
 Version 1.2: https://photos.app.goo.gl/fHoPxXP8cyvYtcUp7
 
 Version 2.0: https://photos.app.goo.gl/fDD1ZjiXjjBxbCRw7
 
 Version 2.0 on PCB: https://photos.app.goo.gl/Gry9ymM6xe9CJ1FB7 
 
 Final Version: https://photos.app.goo.gl/j4gxkzp7DYKLtmJf8

 # Device Runtime calculation: #

 * Assuming this device is powered with a 9V Alkaline battery (which has a capacity of ~500 mAh)
 * The Arduino Uno draws~ ~50 mA of power
 * The LED draws ~ 15mA of power when on
 * The buzzer draws ~7mA of power when on
 
 * When the device is OFF: Battery life is ~ 500mAh/50mA = **10 hours**.
 * When the device is ON: Battery life is ~ 500mAh/(50+20)mA = **7.14 hours**.
     * I simplified 15mA + 7mA = 20mA because the LED has different modes, and the buzzer is not always on. 
 
 To improve battery life, there are a lot of different modifications I can make:
  * Replace the Arudino Uno with a microprocessor that draws less power (eg: Arduino Nano, Arduino Tiny, etc)
  * Reduce the power drawn from the voltage regulator circuitry
  * Replace the battery with a better rated battery
  * etc
