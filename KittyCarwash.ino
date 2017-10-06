    /*******************************************************           
    * Kitty Catwash --  This code keeps kitties clean      *   
    *                                                      *
    * DIGF-6037-001 Creation & Computation                 *                                    *   
    *                                                      *  
    * Material MadLibs 1                                   *
    *                                                      * 
    * Group: Sean, Max, Chris                              *   
    *                                                      *   
    * Purpose:  Demonstration of a simple program.         *   
    *                                                      *   
    * Usage:                                               *   
    *  Connects to the Adafruit Feather M0 ATWINC1500 Wifi *
    *                                                      *
    ********************************************************/  

/*
    * An early version of this program made use of code adapted from Jeremy Rigor -
     *https://arduino.stackexchange.com/questions/17536/controlling-servo-motors-with-push-button-problem-though
*/

#include <Servo.h>

const int buttonPin = 13;          //In a previous version, this was Pin 9, but the docs say: "This analog input is connected to a voltage divider for
// the lipoly battery so be aware that this pin naturally 'sits' at around 2VDC due to the resistor divider". Switched to pin 6.
const int servoPin = 6;

int buttonState = LOW;            //Initialize a variable to track whether the button is pressed
int pos = 1;                      //Servo position in degrees

Servo servoOne;                   //Create a servo object

void setup()
{

  servoOne.attach(servoPin);                //Servos are connected to the same pin for their control signal
  pinMode(buttonPin, INPUT);                //When the switch is open, the buttonPin voltage floats. Adding PULLUP ensures it goes to HIGH
}

void loop()
{
  // Serial.println(buttonState);            //This is for test & debug purposes. We can use Serial Monitor to see what state the Arduino sees the switch in.
  buttonState = digitalRead(buttonPin);

  while (buttonState == HIGH) {
    /*Check the buttonState once for each loop. If it's HIGH, take the servomotor from 1 to 60 degrees and back to 1,
       and then recheck the buttonState and repeat.

       Returning to 1 degree ensures the servo is always "parked" in the same position, and avoids a sudden full-power lurch when the
       arduino is connected to power.

       We used 1 degree rather than 0 because one of our test servos was straining against
       the hard stop when set to zero.
    */

    for (pos = 1; pos < 60; pos++) {
      servoOne.write(pos);
      delay(2);                         //delay 2ms to ensure servo has time to complete the move
    }

    for (pos = 60; pos > 2; pos--) {
      servoOne.write(pos);
      delay(2);
    }
    buttonState = digitalRead(buttonPin);
  }
}
