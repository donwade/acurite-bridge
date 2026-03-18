#include <HardwareSerial.h>
#include <ArduinoLog.h>

#ifdef ARDUINO_M5STACK_Core2
	#include <M5Unified.h>
	#include "SingleStep.hpp"
#endif


#include "weatherBridge/LokiLogger.hpp"
#include "weatherBridge/WeatherBridge.hpp"

#define SERIAL_BAUD 115200 
#define CONFIG_MODE_BUTTON_PIN 4

WeatherBridge weatherBridge = WeatherBridge(SPIFFS, CONFIG_MODE_BUTTON_PIN); // NOLINT(*-interfaces-global-init)

void setup() {
    Serial.begin(SERIAL_BAUD);
    Log.begin(LOG_LEVEL_TRACE, &Serial);

#ifdef LOKI_LOGGING_ENABLED
    LokiLogger::begin(LOKI_URL, LOKI_USERNAME, LOKI_PASSWORD);
#else
    LokiLogger::beginNoop();
#endif

    M5.begin();
    
    M5.Display.fillScreen(TFT_BLACK);                           
    M5.Display.setTextColor(TFT_GREEN);
    M5.Display.setCursor(0, 0);
    M5.Display.display(); delay(1000);

    // https://HWstack.lang-ship.com/howto/m5gfx/font/
    M5.Lcd.setFont(&fonts::FreeSansBold18pt7b);
    M5.Display.printf("hi don %d\n", 6969);
    M5.Display.display(); delay(1000);

    M5.Display.setTextColor(TFT_RED);
    M5.Lcd.setFont(&fonts::FreeMono9pt7b);
    M5.Display.printf("hi sandi %d\n", 1234);
    M5.Display.display(); delay(1000);

    M5.Display.setTextColor(TFT_YELLOW);
    M5.Lcd.setFont(&fonts::FreeMonoOblique12pt7b);
    M5.Display.printf("hi siran %d\n", 1234);
    M5.Display.display(); delay(1000);

	WAIT
   
    
    
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    if (!SPIFFS.begin(false)) {
        for (;;) {
            Log.errorln("An error has occurred while mounting SPIFFS");
            delay(1000);
        }
#pragma clang diagnostic pop
    }
    
	WAIT
    weatherBridge.begin();
    LokiLogger::Instance.writeLog("WeatherExporter initialized");
}

void loop() {
    weatherBridge.loop();
    // testing weatherBridge.configModeButton.isPressed();
}
