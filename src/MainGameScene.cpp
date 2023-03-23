#include "MainGameScene.h"

#include <glm/vec3.hpp>
#include <utilities.h>
#include <cmath>

#include "InputManager.hpp"
#include "Player.h"
#include "ObjEntity.h"
#include "SlenderEntity.h"
#include "PageEntity.h"
#include "TreeEntity.h"
#include "CameraAlternatorEntity.h"

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

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
    this->music = AudioManager::makeSound("../../assets/audio/music1.wav", true);
    AudioManager::playSound(this->music);

    this->skybox = new Skybox();

    // Spawn player in between the two tree rings
    Player* p = new Player();
    p->position.z = -70;
    this->entities.push_back(p);

    // Dense inner and outer tree rings
    spawnTrees(this, 80, glm::vec3(0), 20, 60);
    spawnTrees(this, 300, glm::vec3(0), 80, 110);

    ObjEntity* plane = new ObjEntity("../../assets/objects/plane/plane.obj");
    plane->scale = glm::vec3(1, 1, 1);
    this->entities.push_back(plane);

    this->entities.push_back(new SlenderEntity(p));

    PageEntity* page1 = new PageEntity(glm::vec3(0, 1, 1), 0);
    this->entities.push_back(page1);

    CameraAlternatorEntity* cam = new CameraAlternatorEntity(p, {page1});
    this->entities.push_back(cam);
    this->camera = cam;
}

MainGameScene::~MainGameScene() {
    for (Entity* e : this->entities) {
        delete e;
    }
    AudioManager::destroySound(this->music);
}

void MainGameScene::update(float deltaTime) {
    for (Entity* e : this->entities) {
        e->update(deltaTime);
    }
}

void MainGameScene::draw() {
    this->skybox->draw(this->camera);

    for (Entity* e : this->entities) {
        e->draw(this->camera);
    }
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

        TreeEntity* tree = new TreeEntity(
            glm::vec3(x, 0, z) + origin,
            tiltZ,
            tiltX
        );
        s->entities.push_back(tree);
    }
}
