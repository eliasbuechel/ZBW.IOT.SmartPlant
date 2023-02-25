#include <Arduino.h>

#include <WiFi/WiFiManager.h>
#include <MQTT/MqttClient.h>
#include <StopWatch.h>

#include <Sparkfun_Qwiic_Button.h>
#include <QwiicLedStick.h>

#include <cstring>
#include <string>

#include <Path.h>
#include "LedUtils.h"

#include "SmartPlant/components/SmartPlant.h"


// ----- SETUP -----
static LED* _leds;
static QwiicButton* _button;

static bool initLeds()
{
  Serial.print("Initializing LEDs...   ");
  
  _leds = new LED();
  bool success = _leds->begin();
  success = success && _leds->setLEDBrightness(1);
  
  Serial.print(success ? "-> success" : "-> failed");
  return success;
}

static bool initButton()
{
  Serial.print("Initializing Button...   ");
  
  _button = new QwiicButton();
  bool success = _button->begin();
  success = success && _button->LEDconfig(1, 0, 0);

  Serial.print(success ? "-> success" : "-> failed");
  return success;
}

static bool initQwiicPeripherals()
{
  bool success = Wire.begin();
  Wire.setClock(10000); // We lower the clock here in order to reduce I2C stalls for larger QWIIC systems.

  success = success && initLeds();
  success = success && initButton();

  return success;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting communication demo...");

  bool success = initQwiicPeripherals();

  if (success)
  {
    Serial.println("Peripherals successful initialized, continuing startup...");
    return;
  }

  Serial.println("Initialization failed at some point. Halting...");
  while(true);
}


// ----- LOOP -----
static ZbW::StopWatch cycleTime = ZbW::StopWatch(100);
static bool cycleFlag = false;

static bool execute()
{
  SmartPlant::execute(*_leds);

  return true;
}

void loop() {
  cycleTime.restart();
  cycleFlag = !cycleFlag;
  _leds->setLEDColor(9, 0, cycleFlag ? 255 : 0, 0);

  execute();

  while (!cycleTime.isTimeout())
    delay(5);
}

