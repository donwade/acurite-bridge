#pragma once
#define MY_GFX Adafruit_GFX

#include "Adafruit_GFX.h"
#include "weatherBridge/WeatherBridgeContext.hpp"

class DisplayPage {
protected:
    Adafruit_GFX &delegate;

    explicit DisplayPage(MY_GFX &display);
public:
    virtual void paint(WeatherBridgeContext context);
};
