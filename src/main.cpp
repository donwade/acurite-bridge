#include <HardwareSerial.h>
#include <ArduinoLog.h>
//#include <M5Stack.h>

#ifdef ARDUINO_M5STACK_CORES3
    #include "M5CoreS3.h" 
    #define HW CoreS3
#else
	#include <M5Unified.h>
	#define HW M5
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

#ifdef ARDUINO_M5STACK_CORES3
	auto cfg = M5.config();
	 HW.begin(cfg);
	 int textsize = HW.Display.height() / 60;
	 if (textsize == 0) {
		 textsize = 1;
	 }
	 HW.Display.setTextSize(textsize);
#else
    HW.begin();
#endif
    
    HW.Display.fillScreen(TFT_BLACK);                           
    HW.Display.setTextColor(TFT_GREEN);
    HW.Display.setCursor(0, 0);

    https://HWstack.lang-ship.com/howto/m5gfx/font/
    HW.Lcd.setFont(&fonts::FreeSansBold18pt7b);
    HW.Display.printf("hi don %d\n", 6969);

    HW.Display.setTextColor(TFT_RED);
    HW.Lcd.setFont(&fonts::FreeMono9pt7b);
    HW.Display.printf("hi sandi %d\n", 1234);

    HW.Display.setTextColor(TFT_YELLOW);
    HW.Lcd.setFont(&fonts::FreeMonoOblique12pt7b);
    HW.Display.printf("hi siran %d\n", 1234);


    HW.Display.setTextColor(TFT_WHITE);
    HW.Display.setCursor(0, 10);
    HW.Display.display();
    
    
    
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    if (!SPIFFS.begin(false)) {
        for (;;) {
            Log.errorln("An error has occurred while mounting SPIFFS");
            delay(1000);
        }
#pragma clang diagnostic pop
    }

    weatherBridge.begin();
    LokiLogger::Instance.writeLog("WeatherExporter initialized");
}

void loop() {
    weatherBridge.loop();
    // testing weatherBridge.configModeButton.isPressed();
}
