#include "PageEntity.h"

#include <utilities.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"

PageEntity::PageEntity(glm::vec3 position, std::string name) : ObjEntity("../../assets/objects/pages/" + name + ".obj")
{
    this->rotation.z = deg2rad(90);
    this->position = position;
    this->rotation.y = 0;
    this->hitZone = new HitSphere(this, this->position, 1);
    CollisionManager::registerZone(this->hitZone);
}

void PageEntity::update(float delta) {
    this->rotation.y += delta;
}
