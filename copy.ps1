& $PSScriptRoot/build.ps1
if ($?) {
    adb push libs/arm64-v8a/libfuckmaps.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libfuckmaps.so
    if ($?) {
        & $PSScriptRoot/restart-game.ps1
        if ($args[0] -eq "--log") {
            & $PSScriptRoot/start-logging.ps1
        }
    }
}