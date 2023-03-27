#include "MenuScene.h"

#include <glm/vec3.hpp>
#include <cmath>

#include "CollisionManager.h"
#include "MainGameScene.h"

MenuScene::MenuScene(float noisiness)
{
    this->player = this->addEntity(new Player());
    this->camera = this->player;
    this->player->sanity = 1 - noisiness;

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

    // Wait "delay" seconds before starting to heal
    if (delay <= 0) {
        // Heal player
        this->player->sanity = std::min(1.0f, this->player->sanity+dt);
    } else {
        delay -= dt;
    }

    HitSphere* zone = CollisionManager::insideZone(this->player->position);

    if (zone == this->playPage->hitZone) {
        return new MainGameScene();
    } else if (zone == this->quitPage->hitZone) {
        return nullptr;
    }

    return this;
}
