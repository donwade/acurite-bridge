#include "weatherBridge/InputPullUpButton.hpp"

#include <ArduinoLog.h>

InputPullUpButton::InputPullUpButton(uint8_t pin) noexcept: pin(pin) {}

#ifndef ARDUINO_M5STACK_Core2
void InputPullUpButton::begin() const noexcept {
    Log.infoln("Creating InputPullUpButton on pin %d", pin);
    pinMode(pin, INPUT_PULLUP);
    delay(100);
}

bool InputPullUpButton::isPressed() const noexcept {
    return digitalRead(pin) == 0;
}
#else

// TODO still doesn't work reliably 

#include "M5Unified.h"
#include "M5GFX.h"

void InputPullUpButton::begin() const noexcept {

	M5.update();
	
	uint32_t w = M5.Lcd.width();
	uint32_t h = M5.Lcd.height();

	delay(1000); // allow touch screen to settle
	M5.Display.drawString("UNKNOWN", 0 /*x*/, h -20 /*y*/, &fonts::FreeMonoBold12pt7b);
    Log.infoln("M5 touch buttons (pin %d not needed)", pin);
}


bool InputPullUpButton::isPressed() const noexcept {
	bool ret = false;
	uint32_t old = millis();

	while (old + 100 > millis())
	{
		M5.update();
		if(M5.BtnA.isPressed() || M5.BtnB.isPressed() || M5.BtnC.isPressed())
	    {
	    	ret = true;
	    	break;
	    }
	}
#if 1
	#define FG_GREEN "\033[0;31m"
	#define FG_RED   "\033[0;31m"
	#define FG_DONE  "\033[0m"

	uint32_t w = M5.Lcd.width();
	uint32_t h = M5.Lcd.height();
	
	char msg[30];
	sprintf(msg, "BUTTON-%s", ret ? "DN":"UP");

	M5.Display.drawString(msg, 0 /*x*/, h -20 /*y*/, &fonts::FreeMonoBold12pt7b);
	M5.update();  // update display

	if (ret)
    	Log.infoln(FG_GREEN "KEY-DN" FG_DONE);
    else
		Log.infoln(FG_RED "KEY_UP" FG_DONE);
#endif
	
	return ret;
}
    
#endif

