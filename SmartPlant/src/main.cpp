#include <Arduino.h>

#include "SmartPlant/library/Communication.h"
#include <Path.h>
#include <Sparkfun_Qwiic_Button.h>
#include <QwiicLedStick.h>

#include <StopWatch.h>

#include <cstring>
#include <string>

#include "SmartPlant/components/SmartPlant.h"

// ----- SETUP -----
static LED leds = LED();
static QwiicButton button = QwiicButton();

static bool initLeds();
static bool initButton();
static bool initQwiicPeripherals();

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting Smartplant...");

  initQwiicPeripherals();
  Communication::connecting();
  SmartPlant::configure();
}

static bool initLeds()
{
  Serial.print("\tInitializing LEDs...   ");
  
  bool success = leds.begin();
  success = success && leds.setLEDBrightness(1);
  
  Serial.println(success ? "-> success" : "-> failed");
  return success;
}

static bool initButton()
{
  Serial.print("\tInitializing Button...   ");
  
  bool success = button.begin();
  success = success && button.LEDconfig(1, 0, 0);

  Serial.println(success ? "-> success" : "-> failed");
  return success;
}

static bool initQwiicPeripherals()
{
  Serial.println("Initializing Qwiic peripherals...");

  bool success = Wire.begin();
  Wire.setClock(10000); // We lower the clock here in order to reduce I2C stalls for larger QWIIC systems.

  success = success && initLeds();

  if (!success)
  {
    Serial.println("Initialization failed at some point. Halting...");
    while(true);
  }

  success = success && initButton();

  if (!success)
  {
    Serial.println("Initialization failed at some point. Halting...");
    while(true);
  }
  
  Serial.println("Peripherals successful initialized, continuing startup...");
  return true;
}


// ----- LOOP -----
static ZbW::StopWatch cycleTime = ZbW::StopWatch(100);
static bool cycleFlag = false;

static bool execute();

void loop() {
  cycleTime.restart();
  cycleFlag = !cycleFlag;
  leds.setLEDColor(9, 0, cycleFlag ? 255 : 0, 0);

  execute();

  while (!cycleTime.isTimeout())
    delay(5);
}

static bool execute()
{
  Communication::execute();
  SmartPlant::execute(leds, button);

  return true;
}