#include <Arduino.h>

#define FG_DONE "\033[0m"
#define FG_RED        "\033[0;31m"
#define FG_GREEN      "\033[0;32m"
#define FG_YELLOW     "\033[0;33m"
#define FG_BLUE       "\033[0;34m"
#define FG_MAGENTA    "\033[0;35m"
#define FG_CYAN       "\033[0;36m"
#define FG_WHITE      "\033[0;37m"

int wait(const char *filename, uint32_t line)
{
	int key;
	while (Serial.available()) Serial.read();
	Serial.printf(FG_YELLOW "%s:%d >> " FG_DONE, filename, line);
	while (!Serial.available()) delay(50);
	key = Serial.read();
	Serial.println();
	return key;
}
