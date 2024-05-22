// ErrorAnimation.h

#ifndef _ERRORANIMATION_h
#define _ERRORANIMATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<Bas.SinglePinDevice.h>

namespace Bas
{
	// Encapsulate the error animation.
	class ErrorAnimation
	{
	public:
		enum class LogLevel { none = 0, normal };

	private:
		unsigned long startDelay;
		unsigned long duration;
		Bas::SinglePinDevice firstFogger;
		Bas::SinglePinDevice secondFogger;

	public:
		ErrorAnimation(const Bas::SinglePinDevice& firstFogger, const Bas::SinglePinDevice& secondFogger);
		void begin();
		void update();
		void startAnimating();
		void stopAnimating();
		bool isAnimating();
	};
}

#endif

