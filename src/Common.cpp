#include "Common.h"

void ButtonToSound(bool button, bool buttonLast, uint8_t key, uint8_t keyLast, uint8_t channel)
{
  // button press falling edge -> turn sound on
  if((button == false) && (buttonLast == true))
  {
    midiNoteOn(channel,key,127);
  }
  // button pressed, key changed
  else if((button == false) && (key != keyLast))
  {
    midiNoteOff(channel,keyLast,127);
    midiNoteOn(channel,key,127);
  }
  // button off -> turn sound off
  else if(button == true)
  {
    midiNoteOff(channel,keyLast,127);
  }
}