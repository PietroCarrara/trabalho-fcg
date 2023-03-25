#include "CameraAlternatorEntity.h"

#include <glcommon.h>
#include <utilities.h>

#include "InputManager.hpp"

CameraAlternatorEntity::CameraAlternatorEntity(Player* p, std::list<PageEntity*> pages)
{
    this->player = p;
    this->pages = pages;

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

        // Get the nth page from the list
        auto list = this->pages.begin();
        std::advance(list, this->currentObj - 1);
        PageEntity* p = *list;

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

void CameraAlternatorEntity::onPageRemoved() {
    // In case the page we were looking has been removed,
    // update to make sure we're inside the list bounds
    if (this->currentObj > this->pages.size()) {
        this->currentObj = 0;
    }
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
