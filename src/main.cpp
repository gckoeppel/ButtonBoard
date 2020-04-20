#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Adafruit_ADS1015.h"

#include <Thread.h>
#include <ThreadController.h>

#include "PinDefinitions.h"
#include "midi.h"
#include "ArcadeButtons.h"
#include "Buttons.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

Adafruit_MCP23017 mcp;
Adafruit_ADS1015 ads;

// Global variables to hold all read data
int16_t sliderLeft;
int16_t sliderRight;
bool arcadeRed;
bool arcadeWhite;
bool green;
bool yellow;
bool white;
bool blue;
bool red;
uint8_t switchGreen;
uint8_t switchRed;
int16_t poti0;
int16_t poti1;
int16_t poti2;
int16_t poti3;
float battery_voltage;

// ThreadController that will controll all threads
ThreadController control = ThreadController();

// Thread that blinks the HartBeat LED
Thread HartBeatThread = Thread();

// Thread that gets all input values
Thread GetValuesThread = Thread();

// Thread that logs all values
Thread LogValuesThread = Thread();

// Thread that executes sound stuff
Thread SoundThread = Thread();

// Thread that executes sound stuff
Thread LEDThread = Thread();

void Sound()
{
  //midiAllOff(0);
  ArcadeButtons();
  ButtonsSimple();
}

void LED()
{
  ArcadeButtonsLED();
}
   
// Function that blinks the hartbeat led if the battery voltage is good
// LED will stay on if battery voltage is low
void HartBeat()
{
  static bool ledStatus = false;
  ledStatus = !ledStatus;

  digitalWrite(LED_YELLOW, ledStatus);
}

// Function that gets all input data
void GetValues()
{
  sliderLeft = analogRead(SLIDER_LEFT);
  sliderRight = analogRead(SLIDER_RIGHT);

  uint8_t buttons = mcp.readGPIO(1); // Read GPIO B

  arcadeWhite = CHECK_BIT(buttons, BUTTON_ARCADE_WHITE-8);
  arcadeRed = CHECK_BIT(buttons, BUTTON_ARCADE_RED-8);

  green = CHECK_BIT(buttons, BUTTON_GREEN-8);
  yellow = CHECK_BIT(buttons, BUTTON_YELLOW-8);
  white = CHECK_BIT(buttons, BUTTON_WHITE-8);
  blue = CHECK_BIT(buttons, BUTTON_BLUE-8);
  red = CHECK_BIT(buttons, BUTTON_RED-8);

  switchGreen = digitalRead(SWITCH_GREEN);
  switchRed = digitalRead(SWITCH_RED);

  // poti inputs are scaled to 0-1023 and inverted
  poti0 = map(ads.readADC_SingleEnded(ADS_POTI_0), 0, 1670, 1023, 0);
  poti1 = map(ads.readADC_SingleEnded(ADS_POTI_1), 0, 1670, 1023, 0);
  poti2 = map(ads.readADC_SingleEnded(ADS_POTI_2), 0, 1670, 1023, 0);
  poti3 = map(ads.readADC_SingleEnded(ADS_POTI_3), 0, 1670, 1023, 0);

  // measure battery as described in https://learn.adafruit.com/adafruit-feather-32u4-basic-proto/power-management
  // just using a different pin because the original battery pin is blocked by the interface to the audio feather
  float readvbat = analogRead(BATTERY);
  readvbat *= 2;    // we divided by 2, so multiply back
  readvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  battery_voltage = readvbat / 1024;
}

// Logs all measured data, used for debugging
void LogValues()
{
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

  Serial.println("Buttons:");
  Serial.print("Arcade Red:      "); Serial.println(arcadeRed);
  Serial.print("Arcade White:    "); Serial.println(arcadeWhite);
  Serial.print("Green:           "); Serial.println(green);
  Serial.print("Yellow:          "); Serial.println(yellow);
  Serial.print("White:           "); Serial.println(white);
  Serial.print("Blue:            "); Serial.println(blue);
  Serial.print("Red:             "); Serial.println(red);
  Serial.print("Switch Green: ");
  Serial.println(switchGreen);
  Serial.print("Switch Red:   ");
  Serial.println(switchRed);

  Serial.print("Battery Voltage:  "); Serial.println(battery_voltage);
}

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
  ads.setGain(GAIN_ONE);

  // Setup threads
  HartBeatThread.onRun(HartBeat);
  HartBeatThread.setInterval(1000);
  
  GetValuesThread.onRun(GetValues);
  GetValuesThread.setInterval(100);

  LogValuesThread.onRun(LogValues);
  LogValuesThread.setInterval(1000);

  SoundThread.onRun(Sound);
  SoundThread.setInterval(100);

  LEDThread.onRun(LED);
  LEDThread.setInterval(500);

  control.add(&HartBeatThread);
  control.add(&GetValuesThread);
  control.add(&LogValuesThread);
  control.add(&SoundThread);
  control.add(&LEDThread);

  // Loop through LEDs to show we are ready
  int i;
  for(i=0;i<8;i++)
  {
    mcp.digitalWrite(i,HIGH);
    delay(100);
    mcp.digitalWrite(i,LOW);
  }
  mcp.digitalWrite(15,HIGH);
  delay(100);
  mcp.digitalWrite(15,LOW);

  Serial.println("Setup Completed");
}

void loop() {
	// run ThreadController
	// this will check every thread inside ThreadController,
	// if it should run. If yes, he will run it;
	control.run();

  /*
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
  // if white arcade button is pressed, play tone of right slider
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
*/
}

