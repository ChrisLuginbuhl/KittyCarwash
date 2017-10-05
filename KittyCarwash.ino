/*
 * Creation and Computation Experiment 1 - Cat Wash
 * Servo, Button, Blue Foam, Furry
 * Sean Harkin, Chris Luginbuhl, Max Lander
 * 
 * Code taken/adapted/played with/broken/returned to from Jeremy Rigor - 
 * https://arduino.stackexchange.com/questions/17536/controlling-servo-motors-with-push-button-problem-though
 */
#include <Servo.h> //include arduino servo library

const int buttonPin = 13; //pin the button it is attached to, unchangeable
const int servoPin = 9; // pin the servo is attached to, unchangable

int buttonState = 0; // creates variable and sets initial value
int directionState = 0; 
int pos = 0;

Servo servoOne; //declare servo variable 


void setup() 
{
  Serial.begin(9600); // starts serial monitor, for confirming button read
  servoOne.attach(9); //attach servo to pin
  servoOne.write(directionState); //sets initial directionState
  pinMode(buttonPin, INPUT); //sets buttonPin pin to Input 
}

void loop() 
{
 Serial.println(pos); //confirm button read (while we were having circuit issues)
 buttonState = digitalRead(buttonPin); //reads button input and stores it

  if(directionState == 0) //checks for directionState
  {
    if(buttonState == LOW) //when button is pressed do the following
    {
      directionState = 1; //sets directionState to 1 (in order to allow reverse direction movement below)
      for(pos = 0; pos < 60; pos=pos+1) //increments position value by 1 while pos is between 0 and 60
      {
        servoOne.write(pos); //updates/moves servo position 
        delay(2); 
      }
    }
  }

  else if(directionState ==1) //confirms servo is at end of movement and needs to move back
  {
    if(buttonState == LOW) //when button is pressed do the following
    {
     directionState = 0; //return to starting state
     for(pos = 60; pos > 1; pos=pos-1) //incrementally descrease pos value back to 0
     {
        servoOne.write(pos); //update servo again
        delay(2);
     }
    }
  }
}
