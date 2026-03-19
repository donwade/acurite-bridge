
#include "ArduinoLog.h"
#include "weatherBridge/arrayExtensions.hpp"
#include "weatherBridge/display/pages/DateTimePage.hpp"

DateTimePage::DateTimePage(MY_GFX &display) : DisplayPage(display) {}


void DateTimePage::paint(WeatherBridgeContext context) {
    char charBuf[64];
    uint32_t height = 0;

    for (auto &item: charBuf) { item = '-'; }
    struct tm timeInfo{};

    bool localTimeGetResult = getLocalTime(&timeInfo, 1000);
    if (!localTimeGetResult) {
        Log.warningln("Failed to get local time with getLocalTime()");
    }

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(5, height);

    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(2);
    delegate.setCursor(36, height);
    delegate.setTextWrap(false);
    if (strftime(charBuf, ArraySize(charBuf), "%H:%M", &timeInfo) == 0) {
        Log.warningln("Failed to extract HH:mm with strftime()");
    }
    delegate.print(charBuf);

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(5, height);

    
    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(2);
    delegate.setTextWrap(false);
    if (strftime(charBuf, ArraySize(charBuf), "%d-%m-%Y", &timeInfo) == 0) {
        Log.warningln("Failed to extract HH:mm with strftime()");
    }
    delegate.print(charBuf);
    
	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(5, height);

    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("Timezone");

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(5, height);
    
    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(1);
    delegate.setCursor(70, height);
    delegate.setTextWrap(false);
    if (strftime(charBuf, ArraySize(charBuf), "%Z%z", &timeInfo) == 0) {
        Log.warningln("Failed to extract TZ with strftime()");
    }
    delegate.print(charBuf);  // print local TZ.
	
	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(5, height);

    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    if (context.ntpTimeSyncOk) {
        delegate.print("SYNC OK");
    } else {
        delegate.print("NEED SYNC");
    }

    delegate.drawLine(23, 60, 68, 60, 1);
    delegate.drawLine(53, 51, 68, 51, 1);
}
