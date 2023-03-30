#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include <list>

#include "Scene.h"
#include "Player.h"
#include "SlenderEntity.h"
#include "PageEntity.h"
#include "AudioManager.h"
#include "Skybox.h"
#include "CameraAlternatorEntity.h"

class MainGameScene : public Scene
{
private:
  Player* player;
  SlenderEntity* slender;
  Sound* pageGrab;
  CameraAlternatorEntity* alternator;
  std::list<PageEntity*> pages;

public:
  MainGameScene();

  Scene* update(float dt);
};

#endif // MAINGAMESCENE_H
