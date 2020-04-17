#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Adafruit_ADS1015.h"

extern Adafruit_MCP23017 mcp;
extern Adafruit_ADS1015 ads;

extern int16_t sliderLeft;
extern int16_t sliderRight;
extern bool arcadeRed;
extern bool arcadeWhite;
extern uint8_t switchGreen;
extern uint8_t switchRed;
extern int16_t poti0;
extern int16_t poti1;
extern int16_t poti2;
extern int16_t poti3;
