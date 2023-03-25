#include "CollisionManager.h"

#include "matrices.hpp"

std::vector<HitBox> CollisionManager::walls;
std::vector<HitSphere*> CollisionManager::zones;

HitBox::HitBox(glm::vec3 bottomFrontRight, glm::vec3 topBackLeft) {
    this->bottomFrontRight = bottomFrontRight;
    this->topBackLeft = topBackLeft;
}

HitSphere::HitSphere(Entity* owner, glm::vec3 pos, float r) {
    this->owner = owner;
    this->position = pos;
    this->radius = r;
}

// Register an unmovable object
void CollisionManager::registerWall(HitBox hb) {
    walls.push_back(hb);
}

// Register an unmovable object
void CollisionManager::registerZone(HitSphere* hs) {
    zones.push_back(hs);
}

// Checks whether something collides with an unmovable object
bool CollisionManager::collidesWall(HitBox hb) {
    for (HitBox wall : walls) {
        if (hb.topBackLeft.x > wall.bottomFrontRight.x && hb.bottomFrontRight.x < wall.topBackLeft.x && // overlap in the x plane
            hb.topBackLeft.y > wall.bottomFrontRight.y && hb.bottomFrontRight.y < wall.topBackLeft.y && // overlap in the y plane
            hb.topBackLeft.z > wall.bottomFrontRight.z && hb.bottomFrontRight.z < wall.topBackLeft.z) { // overlap in the z plane
            return true;
        }
    }

    return false;
}

HitSphere* CollisionManager::insideZone(glm::vec3 position) {
    for (HitSphere* zone : zones) {
        float distance = norm(position - zone->position);
        if (distance <= zone->radius) {
            return zone;
        }
    }

    return nullptr;
}