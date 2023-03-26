#include "MenuScene.h"

#include <glm/vec3.hpp>

#include "CollisionManager.h"
#include "MainGameScene.h"

MenuScene::MenuScene()
{
    this->player = this->addEntity(new Player());
    this->camera = this->player;

    this->playPage = this->addEntity(new PageEntity(glm::vec3(1, 1, 3), "play"));
    this->quitPage = this->addEntity(new PageEntity(glm::vec3(-1, 1, 3), "quit"));

    this->song = AudioManager::makeSound("../../assets/audio/slender.mp3", true, 1, true);
    AudioManager::playSound(this->song);
}

MenuScene::~MenuScene()
{
    AudioManager::destroySound(this->song);
}

Scene* MenuScene::update(float dt) {
    Scene::update(dt);

    HitSphere* zone = CollisionManager::insideZone(this->player->position);

    if (zone == this->playPage->hitZone) {
        return new MainGameScene();
    } else if (zone == this->quitPage->hitZone) {
        return nullptr;
    }

    return this;
}
