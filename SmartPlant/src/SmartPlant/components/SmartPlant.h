#pragma once

#include <QwiicLedStick.h>
#include <Sparkfun_Qwiic_Button.h>

namespace SmartPlant
{
    bool configure();
    bool execute(LED& leds, QwiicButton& button);
}