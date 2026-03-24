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
    
    delegate.drawBitmap(9, 5, image_weather_temperature_bits, 16, 16, 1);
    delegate.setTextColor(TFT_YELLOW);
    delegate.setTextSize(2);
    
    delegate.setTextWrap(false);
    if (context.measurementsStore.getWindSpeedKmH().hasValue()) {
        //float knots = kmPerHourToKnots(context.measurementsStore.getWindSpeedKmH().getValue());
        //sprintf(buf, "%.1fkts", knots);
        float kph = context.measurementsStore.getWindSpeedKmH().getValue();
        sprintf(buf, "%.1f kph", kph);
        lprintf(buf);
    } else {
 		lprintf("--- kph");
    }
    
    delegate.setTextColor(TFT_GREEN);
    delegate.setTextSize(2);
    delegate.setTextWrap(false);
    if (context.measurementsStore.getTemperatureC().hasValue()) {
        float tempC = context.measurementsStore.getTemperatureC().getValue();
        if (tempC > 0.0) {
            sprintf(buf, "+%.1f C", tempC);
        } else {
            sprintf(buf, "%.1f C", tempC);
        }
        lprintf(buf);
    } else {
        lprintf("--- C");
    }

    delegate.drawBitmap(8, 24, image_weather_wind_bits, 15, 16, 1);
    delegate.setTextColor(TFT_BLUE);
    delegate.setTextSize(1);
    delegate.setTextWrap(false);

	float directionDegrees = 0.;
	float kph = 0.0;
	if (context.measurementsStore.getWindDirectionDeg().hasValue())
	{
		if (context.measurementsStore.getWindGustKmH().hasValue()) 
		{
			kph = context.measurementsStore.getWindGustKmH().getValue();
			lprintf("Gust %.1f %s %.1f", 
					directionDegrees, 
					convertDegreesToWindDirection(directionDegrees), 
					kph);
		} 
		else
		{
			lprintf("Gust ---");
		}

		if (context.measurementsStore.getWindSpeedKmH().hasValue())
		{
			lprintf("Steady .1f %s %.1f", 
				directionDegrees, 
				convertDegreesToWindDirection(directionDegrees), 
				context.measurementsStore.getWindSpeedKmH());
		}
	}
 }

