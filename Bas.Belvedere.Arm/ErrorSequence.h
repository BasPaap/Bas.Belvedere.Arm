// ErrorSequence.h

#ifndef _ERRORSEQUENCE_h
#define _ERRORSEQUENCE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include<Bas.SinglePinDevice.h>

namespace Bas
{
	// Encapsulate the error sequence.
	class ErrorSequence
	{
	public:
		enum class LogLevel { none = 0, normal };

	private:
		const unsigned long startDelay;
		const unsigned long minDuration;
		const unsigned long maxDuration;
				
		Bas::SinglePinDevice fogger;
		bool isStarted;
		bool isFogging;
		unsigned long duration;
		unsigned long sequenceStartTime;
		unsigned long foggerStartTime;

	public:
		ErrorSequence(const Bas::SinglePinDevice& fogger, unsigned long startDelay, unsigned long minDuration, unsigned long maxDuration);
		void update();
		void start();
		void stop();
		void toggle();
	};
}

#endif

