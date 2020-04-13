#include <Arduino.h>
#include "Adafruit_MCP23017.h"

#include "PinDefinitions.h"

Adafruit_MCP23017 mcp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup Running");

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
  int sliderLeft = analogRead(SLIDER_LEFT);
  int sliderRight = analogRead(SLIDER_RIGHT);

  uint8_t buttons = mcp.readGPIO(1); // Read GPIO B
  buttons &= 0x7F; // mask out top bit, it is an output

  uint8_t switchGreen = digitalRead(SWITCH_GREEN);
  uint8_t switchRed = digitalRead(SWITCH_RED);
  
  Serial.println("==============================================");
  Serial.println("Current input values:");
  Serial.print("Slider Left:  ");
  Serial.print(sliderLeft);
  Serial.println();
  Serial.print("Slider Right: ");
  Serial.print(sliderRight);
  Serial.println();
  Serial.print("Buttons:      ");
  Serial.print(buttons, BIN);
  Serial.println();
  Serial.print("Switch Green: ");
  Serial.print(switchGreen);
  Serial.println();
  Serial.print("Switch Red:   ");
  Serial.print(switchRed);
  Serial.println();
  


  delay(500);
}