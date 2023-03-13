#include <glcommon.h>
#include <glm/vec4.hpp>

#include "Player.h"
#include "InputManager.hpp"

Player::Player() {
    this->position.y = 1.80;
}

void Player::update(float deltaTime) {

    // Mouse input
    float dx = InputManager::getMouseDelta().x;
    float dy = InputManager::getMouseDelta().y;

    // Atualizamos parâmetros da câmera com os deslocamentos
    this->rotX -= 0.01*dx;
    this->rotY += 0.01*dy;

    float phimax = 3.141592f/2;
    float phimin = -phimax;

    if (this->rotY > phimax) {
        this->rotY = phimax;
    }

    if (this->rotY < phimin) {
        this->rotY = phimin;
    }

    glm::vec4 w = this->getViewVec();

    w.y = 0.0;


    glm::vec4 u = crossproduct(glm::vec4(0, 1, 0, 0), w);

    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = glm::vec4(0);

    if (InputManager::isKeyDown(GLFW_KEY_W)) {
        movement += w;
    }
    if (InputManager::isKeyDown(GLFW_KEY_S)) {
        movement -= w;
    }
    if (InputManager::isKeyDown(GLFW_KEY_A)) {
        movement += u;
    }
    if (InputManager::isKeyDown(GLFW_KEY_D)) {
        movement -= u;
    }

    if (norm(movement) > 0) {
        movement = movement / norm(movement);
    }

    glm::vec3 mov3 = glm::vec3(movement.x, movement.y, movement.z);

    this->position += mov3 * deltaTime * 5.0f;
}

void Player::draw(Camera* c) {

}

