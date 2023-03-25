#ifndef CUBEENTITY_H
#define CUBEENTITY_H

#include <glcommon.h>
#include <glm/vec3.hpp>

#include "Entity.h"
#include "ObjEntity.h"

class CubeEntity : public Entity
{
    private:
        static ObjEntity* cube;

    public:
        glm::vec3 position;
        float width;
        float height;
        float depth;

        CubeEntity(glm::vec3 position, float width, float height, float depth);


        void update(float dt);
        void draw(Camera *c);
};

#endif // CUBEENTITY_H
