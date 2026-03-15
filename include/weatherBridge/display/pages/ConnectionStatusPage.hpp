#pragma once
#include "M5Unified.h"
#include "M5GFX.h"

#include "Adafruit_GFX.h"
#include "weatherBridge/display/DisplayPage.hpp"
#include "weatherBridge/types.hpp"

class ConnectionStatusPage : public DisplayPage {
public:
    explicit ConnectionStatusPage(MY_GFX &display);

private:
    void paint(WeatherBridgeContext context) override;

private:
    static const char *rssiToSignalString(int rssi) noexcept;
};