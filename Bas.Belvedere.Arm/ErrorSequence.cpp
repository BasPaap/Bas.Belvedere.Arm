// 
// 
// 

#include "ErrorSequence.h"

namespace Bas
{
	ErrorSequence::ErrorSequence(const Bas::SinglePinDevice& fogger, unsigned long startDelay, unsigned long minDuration, unsigned long maxDuration) : fogger{ fogger }, startDelay{ startDelay }, minDuration { minDuration }, maxDuration { maxDuration }
	{
	}

	void ErrorSequence::update()
	{
		if (this->isStarted && 
			!isFogging &&
			millis() - this->sequenceStartTime >= startDelay)
		{
			Serial.println("Turning on fogger.");
			this->fogger.turnOn();
			this->foggerStartTime = millis();
			this->isFogging = true;
		}

		if (this->isFogging &&
			millis() - this->foggerStartTime >= duration)
		{
			this->stop();
		}
	}

	void ErrorSequence::start()
	{
		this->duration = random(this->minDuration, this->maxDuration);

		Serial.print("Starting error sequence with a delay of ");
		Serial.print(this->startDelay);
		Serial.print("ms for a duration of ");
		Serial.print(this->duration);
		Serial.println("ms.");

		this->isStarted = true;
		this->isFogging = false;
		this->fogger.turnOff();

		this->sequenceStartTime = millis();
	}

	void ErrorSequence::stop()
	{
		Serial.println("Stopping fogger.");
		fogger.turnOff();

		Serial.println("Stopping error sequence");
		this->isStarted = false;
		this->isFogging = false;
	}

	void ErrorSequence::toggle()
	{
		if (this->isStarted)
		{
			stop();
		}
		else
		{
			start();
		}
	}
}