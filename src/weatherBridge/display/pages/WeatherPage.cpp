#include "weatherBridge/display/pages/WeatherPage.hpp"
#include "weatherBridge/units.hpp"

static const unsigned char PROGMEM image_weather_temperature_bits[] = {0x1c, 0x00, 0x22, 0x02, 0x2b, 0x05, 0x2a,
                                                                       0x02, 0x2b, 0x38, 0x2a, 0x60, 0x2b, 0x40,
                                                                       0x2a, 0x40, 0x2a, 0x60, 0x49, 0x38, 0x9c,
                                                                       0x80, 0xae, 0x80, 0xbe, 0x80, 0x9c, 0x80,
                                                                       0x41, 0x00, 0x3e, 0x00};
static const unsigned char PROGMEM image_weather_wind_bits[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x03, 0x88,
                                                                0x04, 0x44, 0x04, 0x44, 0x00, 0x44, 0x00, 0x88,
                                                                0xff, 0x32, 0x00, 0x00, 0xad, 0x82, 0x00, 0x60,
                                                                0x00, 0x10, 0x00, 0x10, 0x01, 0x20, 0x00, 0xc0};


WeatherPage::WeatherPage(MY_GFX &display) : DisplayPage(display) {}

void WeatherPage::paint(WeatherBridgeContext context) {
    char buf[10];
    uint32_t height = 0;
    
    delegate.drawBitmap(9, 5, image_weather_temperature_bits, 16, 16, 1);
    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(2);
    
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);
	
    delegate.setTextWrap(false);
    if (context.measurementsStore.getWindSpeedKmH().hasValue()) {
        //float knots = kmPerHourToKnots(context.measurementsStore.getWindSpeedKmH().getValue());
        //sprintf(buf, "%.1fkts", knots);
        float kph = context.measurementsStore.getWindSpeedKmH().getValue();
        sprintf(buf, "%.1fkts", kph);
        delegate.print(buf);
    } else {
        delegate.print("---kph");
    }
    
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);
		
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(2);
    delegate.setTextWrap(false);
    if (context.measurementsStore.getTemperatureC().hasValue()) {
        float tempC = context.measurementsStore.getTemperatureC().getValue();
        if (tempC > 0.0) {
            sprintf(buf, "+%.1fC", tempC);
        } else {
            sprintf(buf, "%.1fC", tempC);
        }
        delegate.print(buf);
    } else {
        delegate.print("---C");
    }
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);

    delegate.drawBitmap(8, 24, image_weather_wind_bits, 15, 16, 1);
    delegate.setTextColor(TFT_BLUE);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    delegate.print("Gust");
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);

    delegate.setTextColor(TFT_CYAN);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    if (context.measurementsStore.getWindDirectorDeg().hasValue()) {
        float directionDegrees = context.measurementsStore.getWindDirectorDeg().getValue();
        delegate.print(convertDegreesToWindDirection(directionDegrees));
    } else {
        delegate.print("---");
    }
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);

    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);
    if (context.measurementsStore.getWindGustKmH().hasValue()) {
        //float knots = kmPerHourToKnots(context.measurementsStore.getWindGustKmH().getValue());
        //sprintf(buf, "%.1fkts", knots);
        float kph = context.measurementsStore.getWindGustKmH().getValue();
        sprintf(buf, "%.1fkts", kph);
        delegate.print(buf);
    } else {
        delegate.print("---kph");
    }
		height += delegate.fontHeight(delegate.getFont());
		Serial.printf("height = %d\n", height);
		delegate.setCursor(29, height);
}

