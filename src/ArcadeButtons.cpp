#include "ArcadeButtons.h"

// Slider Left controls key of tone of red button
// Poti 2 controls instrument of red button
// Slider Right controls key of tone of white button
// Poti 3 controls instrument of white button
void ArcadeButtons()
{
  static bool arcadeRedLast = true;
  static bool arcadeWhiteLast = true;
  static uint8_t redKeyLast, whiteKeyLast;
  uint8_t redKey, whiteKey;
  
  redKey = AnalogToKey(sliderLeft);
  midiSetInstrument(0, PotiToArcadeInstrument(poti2));
  ButtonToSound(arcadeRed, arcadeRedLast, redKey, redKeyLast, 0);
  arcadeRedLast = arcadeRed;
  redKeyLast = redKey;
  
  whiteKey = AnalogToKey(sliderRight);
  midiSetInstrument(1, PotiToArcadeInstrument(poti3));
  ButtonToSound(arcadeWhite, arcadeWhiteLast, whiteKey, whiteKeyLast, 1);
  arcadeWhiteLast = arcadeWhite;
  whiteKeyLast = whiteKey;
}

// Converts Poti value to Instrument
int PotiToArcadeInstrument(int Poti)
{
  if(Poti < 128)
    return VS1053_GM1_TRUMPET;
  if(Poti < 256)
    return VS1053_GM1_TROMBONE;
  if(Poti < 384)
    return VS1053_GM1_TENOR_SAX;
  if(Poti < 512)
    return VS1053_GM1_OBOE;
  if(Poti < 640)
    return VS1053_GM1_CLARINET;
  if(Poti < 768)
    return VS1053_GM1_FLUTE;
  if(Poti < 896)
    return VS1053_GM1_BLOWN_BOTTLE;
  if(Poti < 1024)
    return VS1053_GM1_OCARINA;
  return VS1053_GM1_SYNTH_BRASS_1;
}

// LEDs in Arcade Buttons blink alternating
void ArcadeButtonsLED()
{
  static bool ledStatus = false;
  ledStatus = !ledStatus;

  if(ledStatus)
  {
      mcp.digitalWrite(LED_ARCADE_RED,HIGH);
      mcp.digitalWrite(LED_ARCADE_WHITE,LOW);
  }
  else
  {
      mcp.digitalWrite(LED_ARCADE_RED,LOW);
      mcp.digitalWrite(LED_ARCADE_WHITE,HIGH);
  }

}