#pragma once

#include <QwiicLedStick.h>
#include "Greenhouse.h"

namespace SmartPlant
{
    namespace Greenhouse_Test
    {
        bool configure();
        bool execute(LED& leds);
    }

    bool configure();
    bool execute(LED& leds);
}