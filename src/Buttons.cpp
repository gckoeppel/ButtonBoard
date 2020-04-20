#include "Buttons.h"

// LEDs chase
// Poti 0 controls key of sound
// Poti 1 controls instrument of buttons
void ButtonsSimple()
{
  static bool greenLast = true;
  static bool yellowLast = true;
  static bool whiteLast = true;
  static bool blueLast = true;
  static bool redLast = true;
  
  static uint8_t keyLast;
  uint8_t key;
  
  key = AnalogToKey(poti0);
  
  SetButtonInstruments(poti1);

  ButtonToSound(green, greenLast, key, keyLast, 2);
  greenLast = green;  
  ButtonToSound(yellow, yellowLast, key, keyLast, 3);
  yellowLast = yellow;
  ButtonToSound(white, whiteLast, key, keyLast, 4);
  whiteLast = white;
  ButtonToSound(blue, blueLast, key, keyLast, 5);
  blueLast = blue;
  ButtonToSound(red, redLast, key, keyLast, 6);
  redLast = red;

  keyLast = key;
}

void ButtonsLEDChase()
{
  static int ledOn = 0;

  mcp.digitalWrite(ledOn,LOW);

  if(ledOn == LED_BUTTON_RED)
  {
    ledOn = LED_BUTTON_GREEN;
  }
  else
  {
    ledOn += 1;
  }

  mcp.digitalWrite(ledOn,HIGH);
}

void SetButtonInstruments(int Poti)
{
  if(Poti < 128)
  {
    midiSetInstrument(2, VS1053_GM1_SOUND_TRACK);
    midiSetInstrument(3, VS1053_GM1_RAIN);
    midiSetInstrument(4, VS1053_GM1_CRYSTAL);
    midiSetInstrument(5, VS1053_GM1_ATMOSHPERE);
    midiSetInstrument(6, VS1053_GM1_BRIGHTNESS);
    return;
  }
  if(Poti < 256)
  {
    midiSetInstrument(2, VS1053_GM1_GOBLINS);
    midiSetInstrument(3, VS1053_GM1_ECHOES);
    midiSetInstrument(4, VS1053_GM1_SCI_FI);
    midiSetInstrument(5, VS1053_GM1_TINKLE_BELL);
    midiSetInstrument(6, VS1053_GM1_AGOGO);
    return;
  }
  if(Poti < 384)
  {
    midiSetInstrument(2, VS1053_GM1_ACOUSTIC_GRAND_PIANO);
    midiSetInstrument(3, VS1053_GM1_BRIGHT_ACOUSTING_PIANO);
    midiSetInstrument(4, VS1053_GM1_ELECTRIC_GRAND_PIANO);
    midiSetInstrument(5, VS1053_GM1_HONKY_TONK_PIANO);
    midiSetInstrument(6, VS1053_GM1_ELECTRIC_PIANO_1);
    return;
  }
  if(Poti < 512)
  {
    midiSetInstrument(2, VS1053_GM1_REVERSE_CYMBAL);
    midiSetInstrument(3, VS1053_GM1_GUITAR_FRET_NOISE);
    midiSetInstrument(4, VS1053_GM1_SEASHORE);
    midiSetInstrument(5, VS1053_GM1_CHOIR_AAHS);
    midiSetInstrument(6, VS1053_GM1_VOICE_OOHS);
    return;
  }
  if(Poti < 640)
  {
    midiSetInstrument(2, VS1053_GM1_TELEPHONE_RING);
    midiSetInstrument(3, VS1053_GM1_HELICOPTER);
    midiSetInstrument(4, VS1053_GM1_APPLAUSE);
    midiSetInstrument(5, VS1053_GM1_METALLIC);
    midiSetInstrument(6, VS1053_GM1_HALO);
    return;
  }
  if(Poti < 768)
  {
    midiSetInstrument(2, VS1053_GM1_VIOLIN);
    midiSetInstrument(3, VS1053_GM1_VIOLA);
    midiSetInstrument(4, VS1053_GM1_CELLO);
    midiSetInstrument(5, VS1053_GM1_CONTRABASS);
    midiSetInstrument(6, VS1053_GM1_TREMOLO_STRINGS);
    return;
  }
  if(Poti < 896)
  {
    midiSetInstrument(2, VS1053_GM1_NEW_AGE);
    midiSetInstrument(3, VS1053_GM1_WARM_PAD);
    midiSetInstrument(4, VS1053_GM1_POLYSYNTH);
    midiSetInstrument(5, VS1053_GM1_CHOIR);
    midiSetInstrument(6,VS1053_GM1_BOWED );
    return;
  }
  midiSetInstrument(2, VS1053_GM1_DRAWBAR_ORGAN);
  midiSetInstrument(3, VS1053_GM1_ROCK_ORGAN);
  midiSetInstrument(4, VS1053_GM1_CHURCH_ORGAN);
  midiSetInstrument(5, VS1053_GM1_HARMONICA);
  midiSetInstrument(6, VS1053_GM1_TANGO_ACCORDION);
}

// Idea, not yet implemented
// Only button that has the LED currently on can make a sound
// LED changes periodically
// Poti 0 controls key of sound
// Poti 1 controls speed at which the LED changes position

// Idea, not yet implemented
// Only button that has the LED currently on can make a sound
// LED changes only when the button is pressed
// Poti 0 controls key of sound
// Poti 1 


// Idea, not yet implemented
// Board shows sequence of LEDs, user must push this sequence
// Sound for correct/wrong

