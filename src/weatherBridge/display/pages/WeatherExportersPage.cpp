#include "weatherBridge/display/pages/WeatherExportersPage.hpp"


static const unsigned char PROGMEM image_list_element_tick[] = {0x80, 0xc0, 0xe0};

WeatherExportersPage::WeatherExportersPage(MY_GFX &display) : DisplayPage(display) {}

void WeatherExportersPage::paint(WeatherBridgeContext context) {

	Home();
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextWrap(false);

    lprintf("PWS Weather : %s", getWeatherExporterStatusName(context.exporters.getPwsWeatherExporterStatus()).c_str());

    lprintf("Windy : %s",getWeatherExporterStatusName(context.exporters.getWindyExporterStatus()).c_str());

    lprintf("WUnderground : %s", getWeatherExporterStatusName(context.exporters.getWeatherUndergroundExporterStatus()).c_str());

    lprintf("WindGuru : %s", getWeatherExporterStatusName(context.exporters.getWindGuruExporterStatus()).c_str());
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

