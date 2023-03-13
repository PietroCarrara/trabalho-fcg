#include <glm/vec3.hpp>

#include "MainGameScene.h"
#include "InputManager.hpp"
#include "Player.h"
#include "ObjEntity.h"
#include "SlenderEntity.h"

MainGameScene::MainGameScene() {
    Player* p = new Player();
    this->entities.push_back(p);
    this->camera = p;

    ObjEntity* tree = new ObjEntity("../../assets/objects/tree/N64_Tree.obj");
    tree->scale = glm::vec3(0.1, 0.1, 0.1);
    // this->entities.push_back(tree);

    this->entities.push_back(new SlenderEntity(p));
}


void MainGameScene::update(float deltaTime) {
    for (Entity* e : this->entities) {
        e->update(deltaTime);
    }
}

void MainGameScene::draw() {
    for (Entity* e : this->entities) {
        e->draw(this->camera);
    }
}
