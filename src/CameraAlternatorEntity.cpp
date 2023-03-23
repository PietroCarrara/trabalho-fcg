#include "CameraAlternatorEntity.h"

#include <glcommon.h>

#include "InputManager.hpp"

CameraAlternatorEntity::CameraAlternatorEntity(Player* p, std::vector<PageEntity*> pages)
{
    this->player = p;
    for (PageEntity* p : pages) {
        this->pages.push_back(p);
    }

    this->lookAtCam.distance = 5;
}

void CameraAlternatorEntity::update(float dt) {
    if (InputManager::isKeyPressed(GLFW_KEY_N)) {
        this->currentObj += 1;
        if (this->currentObj > this->pages.size()) {
            this->currentObj = 0;
        }
    }

    if (this->currentObj > 0) {
        PageEntity* p = this->pages[this->currentObj - 1];
        this->lookAtCam.focus = p->position;
    }
}

void CameraAlternatorEntity::draw(Camera* c) {

}

glm::mat4 CameraAlternatorEntity::getMatrix() {
    if (this->currentObj == 0) {
        return this->player->getMatrix();
    }
    return this->lookAtCam.getMatrix();
}

glm::vec4 CameraAlternatorEntity::getViewVec() {
    if (this->currentObj == 0) {
        return this->player->getViewVec();
    }
    return this->lookAtCam.getViewVec();
}
