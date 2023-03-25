#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <list>
#include <glm/vec3.hpp>

#include "Entity.h"

class HitBox;
class HitSphere;

class CollisionManager
{
    private:
        CollisionManager();

        // Things that can't be pushed around (walls, slenderman, etc...)
        static std::list<HitBox*> walls;

        // Things that trigger events (pages to collect, etc...)
        static std::list<HitSphere*> zones;

    public:
        // Register an unmovable object
        static void registerWall(HitBox* hb);
        static void deregisterWall(HitBox* hb);

        // Register a zone
        static void registerZone(HitSphere* hs);
        static void deregisterZone(HitSphere* hs);

        // Checks whether something collides with an unmovable object
        static bool collidesWall(HitBox hb);

        // Checks in which zone is a given point
        static HitSphere* insideZone(glm::vec3 position);
};

class HitBox {
    private:
        glm::vec3 bottomFrontRight, topBackLeft;

    public:
        HitBox(glm::vec3 bottomFrontRight, glm::vec3 topBackLeft);

        friend bool CollisionManager::collidesWall(HitBox hb);
};

class HitSphere {
    private:
        glm::vec3 position;
        float radius;

    public:
        Entity* owner;

        HitSphere(Entity* owner, glm::vec3 pos, float r);

        friend HitSphere* CollisionManager::insideZone(glm::vec3 position);
};

#endif // COLLISIONMANAGER_H
