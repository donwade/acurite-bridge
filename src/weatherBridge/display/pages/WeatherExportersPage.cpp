#include "weatherBridge/display/pages/WeatherExportersPage.hpp"


static const unsigned char PROGMEM image_list_element_tick[] = {0x80, 0xc0, 0xe0};


WeatherExportersPage::WeatherExportersPage(MY_GFX &display) : DisplayPage(display) {}

void WeatherExportersPage::paint(WeatherBridgeContext context) {
    delegate.drawBitmap(3, 7, image_list_element_tick, 3, 3, 1);

    uint32_t height = 0;
    
	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(7, height);
	
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("PWS Weather");

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	
	delegate.setCursor(7, height);
    
    delegate.drawLine(72, 9, 82, 9, 1);
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setCursor(84, height);
    delegate.setTextWrap(false);
    delegate.print(getWeatherExporterStatusName(context.exporters.getPwsWeatherExporterStatus()));

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(7, height);

    delegate.drawBitmap(3, 17, image_list_element_tick, 3, 3, 1);
    delegate.setTextColor(TFT_BLUE);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("Windy");
    delegate.drawLine(37, 19, 82, 19, 1);
    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(1);
    delegate.setCursor(84, height);
    
    delegate.setTextWrap(false);
    delegate.print(getWeatherExporterStatusName(context.exporters.getWindyExporterStatus()));

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(7, height);

    delegate.drawBitmap(3, 27, image_list_element_tick, 3, 3, 1);
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("WUnderground");
    delegate.drawLine(79, 29, 82, 29, 1);
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setCursor(84, height);
    delegate.setTextWrap(false);
    delegate.print(getWeatherExporterStatusName(context.exporters.getWeatherUndergroundExporterStatus()));

	height += delegate.fontHeight(delegate.getFont());
	Serial.printf("height = %d\n", height);
	delegate.setCursor(7, height);

    delegate.drawBitmap(3, 37, image_list_element_tick, 3, 3, 1);
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("WindGuru");
    
    delegate.drawLine(55, 39, 82, 39, 1);
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setCursor(84, height);
    delegate.setTextWrap(false);
    delegate.print(getWeatherExporterStatusName(context.exporters.getWindGuruExporterStatus()));
}

String WeatherExportersPage::getWeatherExporterStatusName(WeatherExporterStatus status) {
    switch (status) {
        case WeatherExporterStatus::OFF:
            return F("OFF");
        case WeatherExporterStatus::OK:
            return F("OK");
        case WeatherExporterStatus::ERROR:
            return F("ERROR");
        case WeatherExporterStatus::INIT:
            return F("INIT");
        case WeatherExporterStatus::NO_DATA:
            return F("NO DATA");
        case WeatherExporterStatus::NTP_ERR:
            return F("NTP ERR");
    }
    return "";
}

