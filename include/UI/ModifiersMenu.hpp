#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "UnityEngine/UI/Toggle.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(FuckMaps, ModifiersMenu, UnityEngine::MonoBehaviour, 

    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, crashHighBPMToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, crashHighBPMValue);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, crashLowBPMToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, crashLowBPMValue);

)