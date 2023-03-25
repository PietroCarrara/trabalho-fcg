#include "MainGameScene.h"

#include <glm/vec3.hpp>
#include <utilities.h>
#include <cmath>

#include "InputManager.hpp"
#include "ObjEntity.h"
#include "SlenderEntity.h"
#include "TreeEntity.h"
#include "CollisionManager.h"
#include "WinScene.h"

/**
 * @brief Spawns N trees uniformly distributed in a "donut" shaped area
 *
 * @param s           The scene to which we'll be adding these trees in
 * @param count       The number of trees to be added
 * @param origin      The center of the "donut"
 * @param innerRadius The radius of the smaller (inner border) circle of the donut
 * @param outerRadius The radius of the larger (outer border) circle of the donut
 */
void spawnTrees(MainGameScene* s, int count, glm::vec3 origin, float outerRadius, float innerRadius);

MainGameScene::MainGameScene() {
    this->pageGrab = AudioManager::makeSound("../../assets/audio/page-grab.wav");
    this->music = AudioManager::makeSound("../../assets/audio/music1.wav", true);
    AudioManager::playSound(this->music);


    this->skybox = new Skybox();

    // Spawn player in between the two tree rings
    this->player = this->addEntity(new Player());
    this->player->position.z = -70;

    // Dense inner and outer tree rings
    spawnTrees(this, 80, glm::vec3(0), 20, 60);
    spawnTrees(this, 300, glm::vec3(0), 80, 110);

    ObjEntity* plane = this->addEntity(new ObjEntity("../../assets/objects/plane/plane.obj"));
    plane->scale = glm::vec3(1, 1, 1);

    this->addEntity(new SlenderEntity(this->player));

    this->pages = {
        this->addEntity(new PageEntity(glm::vec3(0, 1, 1))),
        this->addEntity(new PageEntity(glm::vec3(3, 1, 2))),
    };

    this->alternator = new CameraAlternatorEntity(this->player, this->pages);
    this->addEntity(alternator);
    this->camera = alternator;
}

MainGameScene::~MainGameScene() {
    AudioManager::destroySound(this->music);
}

Scene* MainGameScene::update(float dt) {
    Scene::update(dt);

    HitSphere* zone = CollisionManager::insideZone(this->player->position);
    if (zone != nullptr) {
        this->pages.remove((PageEntity*)zone->owner);
        this->alternator->onPageRemoved();
        this->removeEntity(zone->owner);
        AudioManager::playSound(this->pageGrab);
    }

    if (this->pages.empty()) {
        return new WinScene();
    }
    return this;
}

void MainGameScene::draw() {
    this->skybox->draw(this->camera);
    Scene::draw();
}

void spawnTrees(MainGameScene* s, int count, glm::vec3 origin, float innerRadius, float outerRadius) {
    // Multiply by hundred so we carry to decimal places to the int
    // conversion. Divide by 100.0f later to "push" them back
    float radiusRange = outerRadius - innerRadius;

    for (int i = 0; i < count; i++) {
        float angle = 2*M_PI * (i/(float)count);

        float radius = innerRadius + randomFloat(radiusRange);
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        float tiltAngleVariation = deg2rad(8);
        float tiltZ = randomFloat(tiltAngleVariation) - tiltAngleVariation/2;
        float tiltX = randomFloat(tiltAngleVariation) - tiltAngleVariation/2;

        s->addEntity(new TreeEntity(
            s,
            glm::vec3(x, 0, z) + origin,
            tiltZ,
            tiltX
        ));
    }
}
