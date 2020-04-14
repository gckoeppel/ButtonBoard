#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Adafruit_ADS1015.h"

#include "PinDefinitions.h"
#include "midi.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

Adafruit_MCP23017 mcp;
Adafruit_ADS1015 ads;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup Running");

  // midi setup
  VS1053_MIDI.begin(31250); // MIDI uses a 'strange baud rate'
  midiSetChannelBank(0, VS1053_BANK_MELODY);
  midiSetChannelVolume(0, 127);
  midiSetInstrument(0, VS1053_GM1_OCARINA);

  // setup of feather pins
  pinMode(LED_GREEN_LEFT, OUTPUT); 
  
  pinMode(SWITCH_RED, INPUT_PULLUP);
  pinMode(SWITCH_GREEN, INPUT_PULLUP);
  pinMode(LED_YELLOW_TOP, OUTPUT);

  pinMode(LED_YELLOW_BOTTOM, OUTPUT);
  pinMode(LED_GREEN_RIGHT, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // setup of mcp gpio expander board
  mcp.begin();                // use default address 0
  mcp.pinMode(LED_BUTTON_GREEN, OUTPUT);
  mcp.pinMode(LED_BUTTON_YELLOW, OUTPUT);
  mcp.pinMode(LED_BUTTON_WHITE, OUTPUT);
  mcp.pinMode(LED_BUTTON_BLUE, OUTPUT);
  mcp.pinMode(LED_BUTTON_RED, OUTPUT);
  mcp.pinMode(LED_ARCADE_RED, OUTPUT);
  mcp.pinMode(LED_ARCADE_WHITE, OUTPUT);
  mcp.pinMode(LED_SWITCH_GREEN, OUTPUT);
  
  mcp.pinMode(BUTTON_GREEN, INPUT);
  mcp.pullUp(BUTTON_GREEN, HIGH);
  mcp.pinMode(BUTTON_YELLOW, INPUT);
  mcp.pullUp(BUTTON_YELLOW, HIGH);
  mcp.pinMode(BUTTON_WHITE, INPUT);
  mcp.pullUp(BUTTON_WHITE, HIGH);
  mcp.pinMode(BUTTON_BLUE, INPUT);
  mcp.pullUp(BUTTON_BLUE, HIGH);
  mcp.pinMode(BUTTON_RED, INPUT);
  mcp.pullUp(BUTTON_RED, HIGH);
  mcp.pinMode(BUTTON_ARCADE_RED, INPUT);
  mcp.pullUp(BUTTON_ARCADE_RED, HIGH);
  mcp.pinMode(BUTTON_ARCADE_WHITE, INPUT);
  mcp.pullUp(BUTTON_ARCADE_WHITE, HIGH);
  mcp.pinMode(LED_SWITCH_RED, OUTPUT);

  // ADS analog digital converter
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);

  int i;
  for(i=0;i<8;i++)
  {
    mcp.digitalWrite(i,HIGH);
    delay(200);
    mcp.digitalWrite(i,LOW);
  }
  mcp.digitalWrite(15,HIGH);
  delay(200);
  mcp.digitalWrite(15,LOW);

  Serial.println("Setup Completed");
}

void loop() {
  // put your main code here, to run repeatedly:

  // get all input data
  int16_t sliderLeft = analogRead(SLIDER_LEFT);
  int16_t sliderRight = analogRead(SLIDER_RIGHT);

  uint8_t buttons = mcp.readGPIO(1); // Read GPIO B
  buttons &= 0x7F; // mask out top bit, it is an output

  uint8_t switchGreen = digitalRead(SWITCH_GREEN);
  uint8_t switchRed = digitalRead(SWITCH_RED);

  int16_t poti0 = ads.readADC_SingleEnded(ADS_POTI_0);
  int16_t poti1 = ads.readADC_SingleEnded(ADS_POTI_1);
  int16_t poti2 = ads.readADC_SingleEnded(ADS_POTI_2);
  int16_t poti3 = ads.readADC_SingleEnded(ADS_POTI_3);
  
  Serial.println("==============================================");
  Serial.println("Current input values:");
  Serial.print("Slider Left:  ");
  Serial.println(sliderLeft);
  Serial.print("Slider Right: ");
  Serial.println(sliderRight);
  
  Serial.print("Poti 0: "); Serial.println(poti0);
  Serial.print("Poti 1: "); Serial.println(poti1);
  Serial.print("Poti 2: "); Serial.println(poti2);
  Serial.print("Poti 3: "); Serial.println(poti3);

  Serial.print("Buttons:      ");
  Serial.println(buttons, BIN);
  Serial.print("Switch Green: ");
  Serial.println(switchGreen);
  Serial.print("Switch Red:   ");
  Serial.println(switchRed);

  // if red arcade button is pressed, play tone of left slider
  if(not CHECK_BIT(buttons, BUTTON_ARCADE_RED-8))
  {
    midiSetInstrument(0, VS1053_GM1_VIBRAPHONE);
    midiNoteOn(0,sliderLeft/12,127);
  }
  
  else if(not CHECK_BIT(buttons, BUTTON_ARCADE_WHITE-8))
  {
    midiSetInstrument(0, VS1053_GM1_ALTO_SAX);
    midiNoteOn(0,sliderRight/12,127);
  }

  else if(not CHECK_BIT(buttons, BUTTON_GREEN-8))
  {
    midiSetInstrument(0, VS1053_GM1_TINKLE_BELL);
    midiNoteOn(0,poti0/168+60,127);
  }
  else if(not CHECK_BIT(buttons, BUTTON_YELLOW-8))
  {
    midiSetInstrument(0, VS1053_GM1_AGOGO);
    midiNoteOn(0,poti0/168+60,127);
  }
  else if(not CHECK_BIT(buttons, BUTTON_WHITE-8))
  {
    midiSetInstrument(0, VS1053_GM1_WOODBLOCK);
    midiNoteOn(0,poti0/168+60,127);
  }
  else if(not CHECK_BIT(buttons, BUTTON_BLUE-8))
  {
    midiSetInstrument(0, VS1053_GM1_TAIKO_DRUM);
    midiNoteOn(0,poti0/168+60,127);
  }
  else if(not CHECK_BIT(buttons, BUTTON_RED-8))
  {
    midiSetInstrument(0, VS1053_GM1_SYNTH_DRUM);
    midiNoteOn(0,poti0/168+60,127);
  }

  else
  {
    midiAllOff(0);
  }  

  delay(100);
}

