/*
 Name:		Bas.Belvedere.Arm.ino
 Created:	5/22/2024 6:08:24 PM
 Author:	Bas Paap
*/

#include "ErrorAnimation.h"
#include <Bas.Button.h>
#include <Bas.SinglePinDevice.h>

const int buttonPin = 2;
const int firstFoggerPin = 3;
const int secondFoggerPin = 4;
const unsigned long debounceDelay = 50; // Amount of milliseconds to debounce

Bas::Button button{ buttonPin, debounceDelay, Bas::Button::LogLevel::normal };
Bas::SinglePinDevice firstFogger{ firstFoggerPin };
Bas::SinglePinDevice secondFogger{ secondFoggerPin };
Bas::ErrorAnimation errorAnimation{ firstFogger, secondFogger };

void setup() 
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial);  // wait for serial port to connect. Needed for native USB port only

    Serial.println("Starting the arm...");

    button.begin(onButtonPressed);
    firstFogger.begin();
    secondFogger.begin();
    errorAnimation.begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    button.update();    
    errorAnimation.update();
}

void onButtonPressed()
{
    if (errorAnimation.isAnimating())
    {
        errorAnimation.stopAnimating();
    }
    else
    {
        errorAnimation.startAnimating();
    }
}
