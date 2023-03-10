#include "MainGameScene.h"
#include "InputManager.hpp"
#include "Player.h"
#include "ObjEntity.h"

MainGameScene::MainGameScene() {
    Player* p = new Player();

    this->entities.push_back(p);
    this->camera = p;

    ObjEntity* theBunny = new ObjEntity("../../assets/objects/firTree.obj", "../../assets/objects/firLeaf.png");

    this->entities.push_back(theBunny);
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
