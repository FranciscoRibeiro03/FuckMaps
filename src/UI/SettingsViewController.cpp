#include "main.hpp"
#include "UI/SettingsViewController.hpp"
#include "Config/ModConfig.hpp"

#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(FuckMaps, SettingsViewController);
using namespace FuckMaps;

void onCrashHighBPMToggle(SettingsViewController* parent, bool newValue) {
    getModConfig().crashHighBPMEnabled.SetValue(newValue, true);
    getLogger().info("Crash on High BPM Maps Toggle changed. New value: %d", newValue);
}

void onCrashHighBPMValueChange(SettingsViewController* parent, float newValue) {
    getModConfig().crashHighBPM.SetValue(newValue, true);
    getLogger().info("Crash on High BPM Maps Value changed. New value: %f", newValue);
}

void onCrashLowBPMToggle(SettingsViewController* parent, bool newValue) {
    getModConfig().crashLowBPMEnabled.SetValue(newValue, true);
    getLogger().info("Crash on Low BPM Maps Toggle changed. New value: %d", newValue);
}

void onCrashLowBPMValueChange(SettingsViewController* parent, float newValue) {
    getModConfig().crashLowBPM.SetValue(newValue, true);
    getLogger().info("Crash on Low BPM Maps Value changed. New value: %f", newValue);
}

void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if (!firstActivation) return;

    getLogger().info("Creating UI options");

    auto layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    // Delegates
    auto onCrashHighBPMToggleDelegate = std::bind(onCrashHighBPMToggle, this, std::placeholders::_1);
    auto onCrashHighBPMValueChangeDelegate = std::bind(onCrashHighBPMValueChange, this, std::placeholders::_1);
    auto onCrashLowBPMToggleDelegate = std::bind(onCrashLowBPMToggle, this, std::placeholders::_1);
    auto onCrashLowBPMValueChangeDelegate = std::bind(onCrashLowBPMValueChange, this, std::placeholders::_1);


    // Anchored Position, for the CreateIncrementSetting function below
    auto anchor = UnityEngine::Vector2(0, 0);


    // Crash on High BPM Maps Toggle
    auto crashHighBPMToggle = QuestUI::BeatSaberUI::CreateToggle(layout->get_transform(), "Crash on High BPM Maps?", getModConfig().crashHighBPMEnabled.GetValue(), onCrashHighBPMToggleDelegate);
    QuestUI::BeatSaberUI::AddHoverHint(crashHighBPMToggle->get_gameObject(), "Enable/disable crashing the game when the song BPM is above a specified value (defined below).");

    // Crash on High BPM Maps Value
    auto crashHighBPMValue = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Max BPM", 0, 5.0f, getModConfig().crashHighBPM.GetValue(), true, false, 0.0f, 1000.0f, anchor,  onCrashHighBPMValueChangeDelegate);
    QuestUI::BeatSaberUI::AddHoverHint(crashHighBPMValue->get_gameObject(), "Set the max BPM. If you try to play a song above this BPM and the toggle above is enabled, your game will crash.");
    
    // Crash on Low BPM Maps Toggle
    auto crashLowBPMToggle = QuestUI::BeatSaberUI::CreateToggle(layout->get_transform(), "Crash on Low BPM Maps?", getModConfig().crashLowBPMEnabled.GetValue(), onCrashLowBPMToggleDelegate);
    QuestUI::BeatSaberUI::AddHoverHint(crashLowBPMToggle->get_gameObject(), "Enable/disable crashing the game when the song BPM is below a specified value (defined below).");

    // Crash on Low BPM Maps Value
    auto crashLowBPMValue = QuestUI::BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Min BPM", 0, 5.0f, getModConfig().crashLowBPM.GetValue(), true, false, 0.0f, 1000.0f, anchor, onCrashLowBPMValueChangeDelegate);
    QuestUI::BeatSaberUI::AddHoverHint(crashLowBPMValue->get_gameObject(), "Set the min BPM. If you try to play a song below this BPM and the toggle above is enabled, your game will crash.");

}