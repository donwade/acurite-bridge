#pragma once

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

    explicit DisplayPage(MY_GFX &display);
public:
    virtual void paint(WeatherBridgeContext context);
};
