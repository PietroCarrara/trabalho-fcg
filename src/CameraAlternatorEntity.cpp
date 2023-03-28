#include "CameraAlternatorEntity.h"

#include <glcommon.h>
#include <utilities.h>

#include "InputManager.hpp"

CameraAlternatorEntity::CameraAlternatorEntity(Player* p, std::list<PageEntity*>* pages)
{
    this->player = p;
    this->pages = pages;

    this->lookAtCam.distance = 5;
}

void CameraAlternatorEntity::update(float dt) {
    if (InputManager::isKeyPressed(GLFW_KEY_N)) {
        this->traveling = true;
    }

    // Pause player when looking at other stuff
    if (this->currentObj > 0) {
        this->player->paused = true;
    } else {
        this->player->paused = false;
    }

    // Update lookat camera
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

    // Animate camera moving
    if (this->traveling) {
        this->progress += dt;

        const auto p1 = this->getPosition(this->currentObj);
        const auto p2 = this->getPosition(this->currentObj + 1);
        const auto p3 = this->progress*p2+(1 - this->progress)*p1;
        this->lookAtCam.focus = p3;

        if (this->progress >= 1) {
            this->progress = 0;
            this->traveling = false;
            this->currentObj += 1;
            if (this->currentObj > this->pages->size()) {
                this->currentObj = 0;
            }
        }
    } else {
        this->lookAtCam.focus = this->getPosition(this->currentObj);
    }
}

glm::vec3 CameraAlternatorEntity::getPosition(int index) {
    index = index % (this->pages->size()+1);

    if (index == 0) {
        return this->player->position;
    }

    auto list = this->pages->begin();
    std::advance(list, index - 1);
    return (*list)->position;
}

void CameraAlternatorEntity::onPageRemoved() {
    // In case the page we were looking has been removed,
    // update to make sure we're inside the list bounds
    if (this->currentObj > this->pages->size()) {
        this->currentObj = 0;
    }
}

glm::mat4 CameraAlternatorEntity::getMatrix() {
    if (this->currentObj == 0 && !this->traveling) {
        return this->player->getMatrix();
    }
    return this->lookAtCam.getMatrix();
}

glm::vec4 CameraAlternatorEntity::getViewVec() {
    if (this->currentObj == 0 && !this->traveling) {
        return this->player->getViewVec();
    }
    return this->lookAtCam.getViewVec();
}
