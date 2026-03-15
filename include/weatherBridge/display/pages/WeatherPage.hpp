#pragma once
#include "M5Unified.h"
#include "M5GFX.h"

#include "Adafruit_GFX.h"
#include "weatherBridge/display/DisplayPage.hpp"

class WeatherPage : public DisplayPage {
public:
    explicit WeatherPage(MY_GFX &display);

private:
    void paint(WeatherBridgeContext context) override;
};


