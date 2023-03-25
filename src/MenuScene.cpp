#include "MenuScene.h"

#include <glm/vec3.hpp>

#include "CollisionManager.h"
#include "MainGameScene.h"

MenuScene::MenuScene()
{
    this->player = this->addEntity(new Player());
    this->camera = this->player;

    this->playPage = this->addEntity(new PageEntity(glm::vec3(1, 1, 2), "play"));
    this->quitPage = this->addEntity(new PageEntity(glm::vec3(-1, 1, 2), "quit"));
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
