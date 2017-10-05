/*
   Code adapted from Jeremy Rigor -
   https://arduino.stackexchange.com/questions/17536/controlling-servo-motors-with-push-button-problem-though
*/
#include <Servo.h>

const int buttonPin = 6;        //In a previous version, this was Pin 9, but the docs say: This analog input is connected to a voltage divider for 
                                // the lipoly battery so be aware that this pin naturally 'sits' at around 2VDC due to the resistor divider 
const int servoPin = 10;

int buttonState = 0;
int directionState = 0;
int pos = 0;

Servo servoOne;                   //Create a servo object

void setup()
{
  Serial.begin(9600);              //This permits communication with the servo  
  
  servoOne.attach(10);             //Servos are connected to the same pin for their control signal
  pinMode(buttonPin, INPUT_PULLUP); //When the switch is open, the buttonPin voltage floats. Adding PULLUP ensures it goes to HIGH
}

void loop()
{
 // Serial.println(buttonState);            //This is for test & debug purposes. We can use Serial Monitor to see what state the Arduino sees the switch in.
  buttonState = digitalRead(buttonPin);   

  if (directionState == 0)
  {
    if (buttonState == LOW)
    {
      directionState = 1;
      for (pos = 0; pos < 60; pos = pos + 1)
      {
        servoOne.write(pos);
        delay(2);
      }
    }
  }

  else
  {
    if (buttonState == LOW)
    {
      directionState = 0;
      for (pos = 60; pos > 1; pos = pos - 1)
      {
        servoOne.write(pos);
        delay(2);
      }
    }
  }
}
