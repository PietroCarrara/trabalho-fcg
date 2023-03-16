#include "CubicBezier.h"

CubicBezier::CubicBezier(float duration, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, bool loop)
{
    this->timer = 0;
    this->duration = duration;
    this->loop = loop;

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

void CubicBezier::update(float dt) {
    this->timer += dt;

    while (this->timer > this->duration && this->loop) {
        this->timer -= this->duration;
    }

    if (this->timer > this->duration) {
        this->timer = this->duration;
    }
}

glm::vec3 CubicBezier::getPoint() {
    const float p = this->timer / this->duration;
    const float i = 1 - p;

    const glm::vec3 p12 = p*p1 + i*p2;
    const glm::vec3 p23 = p*p2 + i*p3;
    const glm::vec3 p34 = p*p3 + i*p4;

    const glm::vec3 p123 = p*p12 + i*p23;
    const glm::vec3 p234 = p*p23 + i*p34;

    return p*p123 + i*p234;
}
