#include "CollisionManager.h"

// Things that can't be pushed around (walls, slenderman, etc...)
std::vector<HitBox> CollisionManager::walls;

HitBox::HitBox(glm::vec3 bottomFrontRight, glm::vec3 topBackLeft) {
    this->bottomFrontRight = bottomFrontRight;
    this->topBackLeft = topBackLeft;
}

// Register an unmovable object
void CollisionManager::registerWall(HitBox hb) {
    walls.push_back(hb);
}

// Checks whether something collides with an unmovable object
bool CollisionManager::collides(HitBox hb) {
    // TODO: Check on the planes along the normals

    for (HitBox wall : walls) {
        if (hb.topBackLeft.x > wall.bottomFrontRight.x && hb.bottomFrontRight.x < wall.topBackLeft.x && // overlap in the x plane
            hb.topBackLeft.y > wall.bottomFrontRight.y && hb.bottomFrontRight.y < wall.topBackLeft.y && // overlap in the y plane
            hb.topBackLeft.z > wall.bottomFrontRight.z && hb.bottomFrontRight.z < wall.topBackLeft.z) { // overlap in the z plane
            return true;
        }
    }

    return false;
}
