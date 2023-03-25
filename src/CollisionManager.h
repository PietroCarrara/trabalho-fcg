#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <glm/vec3.hpp>

class HitBox;

class CollisionManager
{
    private:
        CollisionManager();

        // Things that can't be pushed around (walls, slenderman, etc...)
        static std::vector<HitBox> walls;

    public:
        // Register an unmovable object
        static void registerWall(HitBox hb);

        // Checks whether something collides with an unmovable object
        static bool collides(HitBox hb);
};

class HitBox {

    private:
        glm::vec3 bottomFrontRight, topBackLeft;

    public:
        HitBox(glm::vec3 bottomFrontRight, glm::vec3 topBackLeft);

    friend bool CollisionManager::collides(HitBox hb);
};


#endif // COLLISIONMANAGER_H
