#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Adafruit_ADS1015.h"

#include "midi.h"

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

void ButtonToSound(bool button, bool buttonLast, uint8_t key, uint8_t keyLast, uint8_t channel);
