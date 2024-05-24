/*
 Name:		Bas.Belvedere.Arm.ino
 Created:	5/22/2024 6:08:24 PM
 Author:	Bas Paap
*/

#include "ErrorSequence.h"
#include <Bas.Button.h>
#include <Bas.SinglePinDevice.h>

const int buttonPin = 2;
const int firstFoggerPin = 3;
const int secondFoggerPin = 4;
const unsigned long debounceDelay = 50; // Amount of milliseconds to debounce

const unsigned long errorSequenceStartDelay = 5000;
const unsigned long errorSequenceMinDuration = 10000;
const unsigned long errorSequenceMaxDuration = 20000;
const unsigned long minAutoStartIntervalInMinutes = 2;
const unsigned long maxAutoStartIntervalInMinutes = 4;

unsigned long autoStartIntervalDurationInMinutes;
unsigned long autoStartStartTime;
Bas::Button button{ buttonPin, debounceDelay, Bas::Button::LogLevel::normal };
Bas::SinglePinDevice firstFogger{ firstFoggerPin };
Bas::SinglePinDevice secondFogger{ secondFoggerPin };
Bas::ErrorSequence firstErrorSequence{ firstFogger, errorSequenceStartDelay, errorSequenceMinDuration, errorSequenceMaxDuration };
Bas::ErrorSequence secondErrorSequence{ secondFogger, errorSequenceStartDelay, errorSequenceMinDuration, errorSequenceMaxDuration };

void setup() 
{    
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial);  // wait for serial port to connect. Needed for native USB port only

    Serial.println("Starting the arm...");

    randomSeed(analogRead(0));

    button.begin(onButtonPressed);
    firstFogger.begin();
    secondFogger.begin();

    // When powering up, start the error sequences and set the interval until next time the error sequences start.
    firstErrorSequence.start();
    secondErrorSequence.start();
    setInterval();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    if (millis() - autoStartStartTime >= autoStartIntervalDurationInMinutes * 60000)
    {
        Serial.println("Autostarting error sequences.");
        firstErrorSequence.start();
        secondErrorSequence.start();

        setInterval();        
    }

    button.update();    
    firstErrorSequence.update();
    secondErrorSequence.update();    
}

void onButtonPressed()
{
    firstErrorSequence.toggle();
    secondErrorSequence.toggle();

    setInterval();
}

void setInterval()
{
    Serial.println("Setting new interval.");
    autoStartIntervalDurationInMinutes = random(minAutoStartIntervalInMinutes, maxAutoStartIntervalInMinutes);
    autoStartStartTime = millis();

    Serial.print("Next errror sequence starts in ");
    Serial.print(autoStartIntervalDurationInMinutes);
    Serial.println(" minutes.");
}