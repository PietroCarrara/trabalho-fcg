#include "Player.h"

#include <glm/vec4.hpp>
#include <glcommon.h>
#include <utilities.h>

#include "InputManager.hpp"
#include "CollisionManager.h"
#include "GraphicsManager.hpp"

Player::Player() {
    this->position.y = 1.80;
    this->step = AudioManager::makeSound("../../assets/audio/step.wav", false, 0.4);
}

Player::~Player() {
    AudioManager::destroySound(this->step);
}

void Player::update(float deltaTime) {
    GraphicsManager::setNoisiness(1 - this->sanity);

    // Mouse input
    float dx = InputManager::getMouseDelta().x;
    float dy = InputManager::getMouseDelta().y;

    // Atualizamos parâmetros da câmera com os deslocamentos
    this->rotX -= 0.01*dx;
    this->rotY += 0.01*dy;

    float phimax = M_PI/2 - 0.00001;
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

    glm::vec3 newPos = this->position + glm::vec3(movement.x, movement.y, movement.z) * deltaTime * 5.0f;
    HitBox hb(
      newPos + glm::vec3(-0.5, 0, -0.5f),
      newPos + glm::vec3(0.5, 1.8, 0.5f)
    );
    if  (!CollisionManager::collidesWall(hb)) {
        this->position = newPos;
    }

    if (!AudioManager::isSoundPlaying(this->step) && norm(movement) > 0) {
        AudioManager::playSound(this->step);
    }
}
