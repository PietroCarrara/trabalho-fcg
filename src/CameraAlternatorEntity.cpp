#include "CameraAlternatorEntity.h"

#include <glcommon.h>
#include <utilities.h>

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
        this->player->paused = true;

        PageEntity* p = this->pages[this->currentObj - 1];
        this->lookAtCam.focus = p->position;

        // Mouse input
        float dx = InputManager::getMouseDelta().x;
        float dy = InputManager::getMouseDelta().y;
        this->lookAtCam.rotX -= 0.01*dx;
        this->lookAtCam.rotY += 0.01*dy;

        float phimax = M_PI/2 - 0.00001;
        float phimin = -phimax;
        if (this->lookAtCam.rotY > phimax) {
            this->lookAtCam.rotY = phimax;
        }
        if (this->lookAtCam.rotY < phimin) {
            this->lookAtCam.rotY = phimin;
        }
    } else {
        this->player->paused = false;
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
