// 
// 
// 

#include "Timer.h"

void Bas::Timer::begin(CallbackPointer callback)
{
	if (this->logLevel == LogLevel::normal)
	{
		Serial.println("Initializing timer.");
	}

	this->callback = callback;
}

void Bas::Timer::start(unsigned long duration)
{
	if (this->logLevel == LogLevel::normal)
	{
		Serial.print("Running timer for ");
		Serial.print(duration);
		Serial.println("ms.");
	}

	this->duration = duration;
	this->isRunning = true;
	this->startTime = millis();
}

void Bas::Timer::stop()
{
	Serial.println("Stopping timer.");
	this->isRunning = false;
}

void Bas::Timer::update()
{
	if (isRunning &&
		millis() - this->startTime >= duration)
	{
		if (this->logLevel == LogLevel::normal)
		{
			Serial.print("Timer expired after ");
			Serial.print(this->duration);
			Serial.println("ms.");
		}

		stop();
		this->callback();		
	}
}
