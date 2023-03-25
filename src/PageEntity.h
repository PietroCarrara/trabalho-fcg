#ifndef PAGE_ENTITY_H
#define PAGE_ENTITY_H

#include <glm/vec3.hpp>

#include "Entity.h"
#include "ObjEntity.h"
#include "Camera.hpp"
#include "CollisionManager.h"

class PageEntity : public Entity
{
    private:
        static ObjEntity* page;

    public:
        PageEntity(glm::vec3 position);

        glm::vec3 position;
        float rotation;
        HitSphere* hitZone;

        void update(float delta);
        void draw(Camera* c);
};

#endif // PAGE_ENTITY_H
