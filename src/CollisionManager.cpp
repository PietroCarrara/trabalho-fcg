#include "CollisionManager.h"

#include "matrices.hpp"

std::list<HitBox*> CollisionManager::walls;
std::list<HitSphere*> CollisionManager::zones;

HitBox::HitBox(glm::vec3 bottomFrontRight, glm::vec3 topBackLeft) {
    this->bottomFrontRight = bottomFrontRight;
    this->topBackLeft = topBackLeft;
}

HitSphere::HitSphere(Entity* owner, glm::vec3 pos, float r) {
    this->owner = owner;
    this->position = pos;
    this->radius = r;
}

void CollisionManager::registerWall(HitBox* hb) {
    walls.push_back(hb);
}

void CollisionManager::deregisterWall(HitBox* hb) {
    walls.remove(hb);
}

void CollisionManager::registerZone(HitSphere* hs) {
    zones.push_back(hs);
}

void CollisionManager::deregisterZone(HitSphere* hs) {
    zones.remove(hs);
}

// Checks whether something collides with an unmovable object
bool CollisionManager::collidesWall(HitBox hb) {
    for (HitBox* wall : walls) {
        if (hb.topBackLeft.x > wall->bottomFrontRight.x && hb.bottomFrontRight.x < wall->topBackLeft.x && // overlap in the x plane
            hb.topBackLeft.y > wall->bottomFrontRight.y && hb.bottomFrontRight.y < wall->topBackLeft.y && // overlap in the y plane
            hb.topBackLeft.z > wall->bottomFrontRight.z && hb.bottomFrontRight.z < wall->topBackLeft.z) { // overlap in the z plane
            return true;
        }
    }

    return false;
}

bool CollisionManager::hitsWall(glm::vec3 origin, glm::vec3 direction) {
    // FONTE: https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms#18459
    const float distance = norm(direction);
    const glm::vec3 normDir = direction / distance;
    glm::vec3 invDir = 1.0f / normDir;

    for (HitBox* hb : walls) {
        // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
        // r.org is origin of ray
        float t1 = (hb->bottomFrontRight.x - origin.x)*invDir.x;
        float t2 = (hb->topBackLeft.x - origin.x)*invDir.x;

        float t3 = (hb->bottomFrontRight.y - origin.y)*invDir.y;
        float t4 = (hb->topBackLeft.y - origin.y)*invDir.y;

        float t5 = (hb->topBackLeft.z - origin.z)*invDir.z;
        float t6 = (hb->bottomFrontRight.z - origin.z)*invDir.z;

        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
        if (tmax < 0) {
            continue;
        }

        // if tmin > tmax, ray doesn't intersect AABB
        if (tmin > tmax) {
            continue;
        }

        if (tmin <= distance) {
            return true;
        };
    }

    return false;
}

// Checks if a point is inside a zone
HitSphere* CollisionManager::insideZone(glm::vec3 position) {
    for (HitSphere* zone : zones) {
        float distance = norm(position - zone->position);
        if (distance <= zone->radius) {
            return zone;
        }
    }

    return nullptr;
}

// TODO: Check whether something collides with a plane