#include "Dzwiek.h"
#include "iostream"

Sound sound;
Music music;
Music music2;

void InitSounds() {
    sound = LoadSound("Sounds/Przycisk.wav");
    music = LoadMusicStream("Sounds/bgmusic.ogg");
    music2 = LoadMusicStream("Sounds/bgmusic2.ogg");

    //PlayMusicStream(music);
}

void UnloadSounds() {
    UnloadSound(sound);
    UnloadMusicStream(music);
    UnloadMusicStream(music2);
}