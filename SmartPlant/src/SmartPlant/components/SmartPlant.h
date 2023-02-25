#pragma once

#include <QwiicLedStick.h>
#include "Greenhouse.h"

namespace SmartPlant
{
    namespace Greenhouse_Test
    {
        bool execute(LED& leds);
    }

    bool execute(LED& leds);
}