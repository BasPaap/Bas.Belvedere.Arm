// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class Timer
	{
	public:
		enum class LogLevel { none = 0, normal };
	
	private:
		using CallbackPointer = void(*)();
		CallbackPointer callback;
		unsigned long duration;
		unsigned long startTime;
		bool isRunning;
		LogLevel logLevel;

	public:		
		void begin(CallbackPointer callback);
		void start(unsigned long duration);
		void stop();
		void update();
	};
}

#endif

