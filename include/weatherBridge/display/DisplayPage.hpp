#pragma once
#include <cstdint>

#ifdef ARDUINO_M5STACK_Core2
   #include "M5Unified.h"
   #include "M5GFX.h"
   #define MY_GFX M5GFX
#else
	#include "Adafruit_GFX.h"
	#define MY_GFX Adafruit_GFX
#endif

#include "weatherBridge/WeatherBridgeContext.hpp"

class DisplayPage {
protected:
    MY_GFX &delegate;
	uint32_t vertPixel;
	uint16_t lastMargin;
	char lclBuf[120];
	
	int lprintf(const char* format, ... );
	int lprintf(const String &foo);
	int lprintf(int16_t leftMargin, const String &foo);
	void Home(int16_t marginLeft = 0);

    explicit DisplayPage(MY_GFX &display);

private:
	uint16_t LineAdvance(void);

public:
    virtual void paint(WeatherBridgeContext context);
};
