#include "AudioManager.h"

#include <cstdlib>
#include <cstdio>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

static ma_engine engine;

struct Sound {
  ma_sound sound;
};

Sound* AudioManager::makeSound(const char* fname, bool loop) {
  Sound* s = new Sound();
  ma_sound_init_from_file(&engine, fname, 0, NULL, NULL, &s->sound);
  ma_sound_set_looping(&s->sound, loop);
  return s;
}

void AudioManager::destroySound(Sound* s) {
  ma_sound_uninit(&s->sound);
  delete s;
}

void AudioManager::init() {
  ma_result result;
  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    printf("Failed to initialize audio engine.");
    exit(1);
  }
}

void AudioManager::destroy() {
  ma_engine_uninit(&engine);
}

void AudioManager::playSound(Sound *s) {
  ma_sound_start(&s->sound);
}

void AudioManager::stopSound(Sound *s) {
  ma_sound_stop(&s->sound);
}