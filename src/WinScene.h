#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include "Scene.h"
#include "Player.h"
#include "AudioManager.h"

class WinScene : public Scene {
  private:
    Sound* song;
    Player* player;

  public:
    WinScene();
    ~WinScene();

    Scene* update(float dt);
};

#endif