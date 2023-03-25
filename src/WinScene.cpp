#include "WinScene.h"

#include <utilities.h>
#include <glm/vec3.hpp>

#include "ObjEntity.h"
#include "PageEntity.h"
#include "CollisionManager.h"
#include "MenuScene.h"

WinScene::WinScene() {
  this->player = this->addEntity(new Player());
  this->camera = this->player;

  ObjEntity *slender = this->addEntity(new ObjEntity("../../assets/objects/slender/slender.obj"));
  slender->position.z = 4.5;
  slender->position.x = -1;
  slender->rotation.y = -deg2rad(90+45);

  ObjEntity *table = this->addEntity(new ObjEntity("../../assets/objects/table/Table_Booth_B.obj"));
  table->scale = glm::vec3(0.007);
  table->position.z = 2;
  table->position.x = 1.5;

  ObjEntity *cake = this->addEntity(new ObjEntity("../../assets/objects/cake/BirthdayCake.obj"));
  cake->scale = glm::vec3(0.1);
  cake->position.z = 3;
  cake->position.y = 1;
  cake->position.x = 0;

  this->addEntity(new PageEntity(glm::vec3(0, 1, 5), "win"));

  this->song = AudioManager::makeSound("../../assets/audio/Perfect-Day-Dream.mp3", true, 1, true);
  AudioManager::playSound(this->song);
}

WinScene::~WinScene() {
  AudioManager::destroySound(this->song);
}

Scene* WinScene::update(float dt) {
  Scene::update(dt);

  if (CollisionManager::insideZone(this->player->position)) {
    return new MenuScene();
  }

  return this;
}