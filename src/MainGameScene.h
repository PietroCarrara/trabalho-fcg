#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <list>

#include "AudioManager.h"
#include "Entity.h"
#include "Skybox.h"

class MainGameScene
{
private:
  Skybox* skybox;
  Sound* music;

public:
  Camera* camera;

  MainGameScene();
  ~MainGameScene();
  std::list<Entity*> entities = {};

  void update(float deltaTime);

  void draw();
};

#endif // MAINGAMESCENE_H
