#include <Arduino.h>
#include "Adafruit_MCP23017.h"

#include "PinDefinitions.h"
#include "Common.h"
#include "midi.h"

void ButtonsSimple(bool LED);
void SetButtonInstruments(int Poti);
void ButtonsLEDChase();