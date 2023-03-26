#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <list>

#include "Scene.h"
#include "Player.h"
#include "PageEntity.h"
#include "AudioManager.h"
#include "Skybox.h"
#include "CameraAlternatorEntity.h"

class MainGameScene : public Scene
{
private:
  Player* player;
  Sound* music;
  Sound* pageGrab;
  CameraAlternatorEntity* alternator;
  std::list<PageEntity*> pages;

public:
  MainGameScene();
  ~MainGameScene();

  Scene* update(float dt);
};

#endif // MAINGAMESCENE_H
