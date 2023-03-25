#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include "Scene.h"
#include "AudioManager.h"
#include "Skybox.h"

class MainGameScene : public Scene
{
private:
  Skybox* skybox;
  Sound* music;

public:
  MainGameScene();
  ~MainGameScene();

  void draw();
};

#endif // MAINGAMESCENE_H
