#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

struct Sound;

class AudioManager {
  private:
    AudioManager();

  public:
    static void init();
    static void destroy();

    static Sound* makeSound(const char* fname, bool loop = false, float volume = 1, float stream = false);
    static void destroySound(Sound *s);

    static void playSound(Sound *s);
    static void stopSound(Sound *s);

    static bool isSoundPlaying(Sound *s);
};

#endif