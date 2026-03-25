#pragma once
#ifndef ARDUINO_M5STACK_Core2
  #include "Adafruit_SSD1306.h"
  #define MY_GFX Adafruit_SSD1306
#else
  #include "M5Unified.h"
  #define  MY_GFX M5GFX
#endif

#include "weatherBridge/types.hpp"
#include "weatherBridge/WeatherBridgeContext.hpp"
#include "weatherBridge/display/pages/ConnectionStatusPage.hpp"
#include "weatherBridge/display/pages/DateTimePage.hpp"
#include "weatherBridge/display/pages/WeatherPage.hpp"
#include "weatherBridge/display/pages/WeatherExportersPage.hpp"


class WeatherBridgeDisplay {
private:
    MY_GFX &delegate = M5.Display;
    
    DisplayPage *pages[4]{
            new ConnectionStatusPage(delegate),
            new DateTimePage(delegate),
            new WeatherPage(delegate),
            new WeatherExportersPage(delegate),
    };

    size_t nextPageIndex = 0;
    unsigned long lastPageSwitchMillis = millis();

public:
    WeatherBridgeDisplay();

    ~WeatherBridgeDisplay();

    void begin();

    void displayTimer(WeatherBridgeContext context);

private:
    void nextPage(WeatherBridgeContext context);

    void paintSplash();
};

