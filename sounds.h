#pragma once

#include <windows.h>
#include <mmsystem.h>

bool sound_enabled = getSetting("sound");
bool music_enabled = getSetting("music");

void sndButton() {
    if (sound_enabled) 
        PlaySound(TEXT("button.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sndSSwitch() {
    if (sound_enabled)
        PlaySound(TEXT("sswitch.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sndPong() {
    if (sound_enabled)
        PlaySound(TEXT("pong.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sndWin() {
    if (sound_enabled)
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sndError() {
    if (sound_enabled)
        PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void music() {
    if (music_enabled) {
        mciSendString(TEXT("open \"music.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
    }
}

void stopSound() {
    PlaySound(NULL, 0, 0);
}

void stopMusic() {
    mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
    mciSendString(TEXT("close mp3"), NULL, 0, NULL);
}