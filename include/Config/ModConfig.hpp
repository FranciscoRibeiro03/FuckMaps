#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(crashHighBPMEnabled, bool, "Crash on High BPM Maps?", true);
    CONFIG_VALUE(crashHighBPM, float, "Max BPM", 200.0f);
    CONFIG_VALUE(crashLowBPMEnabled, bool, "Crash on Low BPM Maps?", true);
    CONFIG_VALUE(crashLowBPM, float, "Min BPM", 100.0f);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(crashHighBPMEnabled);
        CONFIG_INIT_VALUE(crashHighBPM);
        CONFIG_INIT_VALUE(crashLowBPMEnabled);
        CONFIG_INIT_VALUE(crashLowBPM);
    )

);