#include <glm/vec3.hpp>

#include "MainGameScene.h"
#include "InputManager.hpp"
#include "Player.h"
#include "ObjEntity.h"
#include "SlenderEntity.h"
#include "PageEntity.h"

MainGameScene::MainGameScene() {
    this->skybox = new Skybox();

    Player* p = new Player();
    this->entities.push_back(p);
    this->camera = p;

    ObjEntity* tree = new ObjEntity("../../assets/objects/tree/N64_Tree.obj");
    tree->scale = glm::vec3(0.1, 0.1, 0.1);
    this->entities.push_back(tree);

    ObjEntity* plane = new ObjEntity("../../assets/objects/plane/plane.obj");
    plane->scale = glm::vec3(1, 1, 1);
    this->entities.push_back(plane);

    this->entities.push_back(new SlenderEntity(p));

    PageEntity* page1 = new PageEntity(glm::vec3(0, 1, 1), 0);
    this->entities.push_back(page1);
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
