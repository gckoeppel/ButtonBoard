#include <Arduino.h>
#include "Adafruit_MCP23017.h"

#include "PinDefinitions.h"
#include "Common.h"
#include "midi.h"

void ArcadeButtons();
void ArcadeButtonsLED();
int PotiToArcadeInstrument(int Poti);
int SliderToKey(int slider);