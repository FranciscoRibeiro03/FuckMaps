#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#include "UnityEngine/UI/Toggle.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DECLARE_CLASS_CODEGEN(FuckMaps, SettingsViewController, HMUI::ViewController,

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, crashHighBPMToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, crashHighBPMValue);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, crashLowBPMToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, crashLowBPMValue);

)