#include "main.hpp"
#include "Config/ModConfig.hpp"
#include "UI/SettingsViewController.hpp"

#include "GlobalNamespace/LevelSelectionNavigationController.hpp"
#include "GlobalNamespace/LevelCollectionNavigationController.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
using namespace GlobalNamespace;

#include "questui/shared/QuestUI.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

bool isSpeedMap = false;
bool isSlowMap = false;
float currBPM = 0.0f;

void Crash() {
    if (isSpeedMap) getLogger().info("CRASHING GAME! Reason: High BPM Map detected.");
    if (isSlowMap) getLogger().info("CRASHING GAME! Reason: Low BPM Map detected.");
    getLogger().info("Current BPM: %f", currBPM);
    getLogger().info("Max BPM: %f", getModConfig().crashHighBPM.GetValue());
    getLogger().info("Min BPM: %f", getModConfig().crashLowBPM.GetValue());
    CRASH_UNLESS(false);
}

MAKE_HOOK_MATCH(PressPracticeButton,
    &LevelSelectionNavigationController::HandleLevelCollectionNavigationControllerDidPressPracticeButton,
    void,
    LevelSelectionNavigationController* self,
    LevelCollectionNavigationController* arg1,
    IBeatmapLevel* iBeatmapLevel)
{
    if (isSpeedMap && getModConfig().crashHighBPMEnabled.GetValue()) Crash();
    if (isSlowMap && getModConfig().crashLowBPMEnabled.GetValue()) Crash();
    PressPracticeButton(self, arg1, iBeatmapLevel);
}

MAKE_HOOK_MATCH(PressPlayButton,
    &LevelSelectionNavigationController::HandleLevelCollectionNavigationControllerDidPressActionButton,
    void,
    LevelSelectionNavigationController* self,
    LevelCollectionNavigationController* viewController)
{
    if (isSpeedMap && getModConfig().crashHighBPMEnabled.GetValue()) Crash();
    if (isSlowMap && getModConfig().crashLowBPMEnabled.GetValue()) Crash();
    PressPlayButton(self, viewController);
}

MAKE_HOOK_MATCH(GetMapInfo,
    &StandardLevelDetailView::RefreshContent,
    void,
    StandardLevelDetailView* self)
{
    GetMapInfo(self);
    isSlowMap = false;
    isSpeedMap = false;
    auto beatmapLevel = self->get_selectedDifficultyBeatmap()->get_level();
    auto previewBeatmapLevel = reinterpret_cast<IPreviewBeatmapLevel*>(beatmapLevel);
    currBPM = previewBeatmapLevel->get_beatsPerMinute();
    if (currBPM < getModConfig().crashLowBPM.GetValue()) isSlowMap = true;
    if (currBPM > getModConfig().crashHighBPM.GetValue()) isSpeedMap = true;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getModConfig().Init(modInfo);
    getConfig().Reload();
    getConfig().Write();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    custom_types::Register::AutoRegister();
    QuestUI::Register::RegisterModSettingsViewController<FuckMaps::SettingsViewController*>(modInfo, "FuckMaps");
    QuestUI::Register::RegisterMainMenuModSettingsViewController<FuckMaps::SettingsViewController*>(modInfo, "FuckMaps");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), PressPracticeButton);
    INSTALL_HOOK(getLogger(), PressPlayButton);
    INSTALL_HOOK(getLogger(), GetMapInfo);
    getLogger().info("Installed all hooks!");
}