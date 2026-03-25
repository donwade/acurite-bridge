
#include "weatherBridge/display/DisplayPage.hpp"

DisplayPage::DisplayPage(MY_GFX &display) : delegate(display), vertPixel(0) {}

void DisplayPage::Home(int16_t marginLeft)
{
	if (marginLeft <= 0) // requesting neg h pos means top home cursor
	{
		vertPixel = 0;
		marginLeft = -marginLeft;
	}
	lastMargin = marginLeft;
	
	// first time using a page, you forgot to set left margin
	assert(vertPixel < 500);
	
	//Serial.printf("Home vertPixel = %d\n", vertPixel);
	
	delegate.setCursor(lastMargin, vertPixel);
}

uint16_t DisplayPage::LineAdvance(void)
{
	// first time using a page, you forgot to set left margin
	assert(vertPixel < 500); 
	
	vertPixel += delegate.fontHeight(delegate.getFont());
	//Serial.printf("vertPixel = %d\n", vertPixel);
	delegate.setCursor(lastMargin, vertPixel);
	return vertPixel;
}

int DisplayPage::lprintf(const String &foo)
{
	int ret = lprintf(foo.c_str());
	return ret;
}

int DisplayPage::lprintf(const char* format, ... )
{
	va_list args;
    va_start(args, format); 

    int ret = vsnprintf(lclBuf, sizeof(lclBuf), format, args);
	delegate.print(lclBuf);
	
	LineAdvance();
	
	Serial.printf("--->  %s\n", lclBuf);
    va_end(args); 
    return ret;
}

void DisplayPage::paint(WeatherBridgeContext context) {}

