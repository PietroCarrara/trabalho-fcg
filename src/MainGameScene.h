#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <list>

#include "Entity.h"
#include "Skybox.h"

class MainGameScene
{
private:
  Skybox* skybox;

public:
  Camera* camera;

  MainGameScene();
  std::list<Entity*> entities = {};

  void update(float deltaTime);

  void draw();
};

#endif // MAINGAMESCENE_H
