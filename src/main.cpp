/*
Name:		ClassyButton.ino
Created:	8/11/2017 10:16:27 PM
Author:	Guillermo
*/

#include "Arduino.h"
#include "Button.h"

Button testButton(2);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop()
{
  //delay(500);
  testButton.Refresh();

  switch (testButton.GetPressType())
  {
  case Button::PressTypes::None:
  {
    break;
  }
  case Button::PressTypes::SingleClick:
  {
    Serial.println("A single click");
    break;
  }
  case Button::PressTypes::DoubleClick:
  {
    Serial.println("That was a double click!");
    break;
  }
  case Button::PressTypes::LongClick:
  {
    Serial.println("Aaaaannnnnndddd that was a long press");
    break;
  }
  }
}
