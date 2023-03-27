#include "DoorEntity.h"
#include "InputManager.hpp"
#include "CollisionManager.h"
#include <utilities.h>

DoorEntity::DoorEntity(Player *p) : ObjEntity("../../assets/objects/door/basementdoor01a.obj")
{
    this->player = p;

    this->scale = glm::vec3(0.013);
    this->position = glm::vec3(-0.6,0,26.3);

    this->isOpening = false;
    this->isClosing = false;
    this->progression = 0.0f;

    this->hitZone = new HitSphere(this, this->position, 3);
    CollisionManager::registerZone(this->hitZone);
}

void DoorEntity::update(float deltaTime) {
    HitSphere* zone = CollisionManager::insideZone(this->player->position);

    if (zone == this->hitZone) {
        if (InputManager::isKeyPressed(GLFW_KEY_E)) {
            interact();
        }
    }

    if (this->isOpening) {
        if (this->progression >= 1.0) {
            this->isOpening = false;
        }
        this->progression += deltaTime;
        this->rotation.y = (progression*deg2rad(180));
    }

    else if (this->isClosing) {
        if (this->progression <= 0.0) {
            this->isClosing = false;
        }
        this->progression -= deltaTime;
        this->rotation.y = (progression*deg2rad(180));
    }
}

void DoorEntity::interact() {
    if (this->progression <= 1.0f) {
        this->isOpening = true;
    }

    else {
        this->isClosing = true;
    }

}
