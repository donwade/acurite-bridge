#pragma once

#include "Adafruit_GFX.h"
#include "weatherBridge/display/DisplayPage.hpp"

class WeatherPage : public DisplayPage {
public:
    explicit WeatherPage(MY_GFX &display);

private:
    void paint(WeatherBridgeContext context) override;
};


