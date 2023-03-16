#ifndef PAGE_ENTITY_H
#define PAGE_ENTITY_H

#include <glm/vec3.hpp>

#include "Entity.h"
#include "ObjEntity.h"
#include "Camera.hpp"

class PageEntity : public Entity
{
    private:
        static ObjEntity* page;

    public:
        PageEntity(glm::vec3 position, float rotation);

        glm::vec3 position;
        float rotation;

        void update(float delta);
        void draw(Camera* c);
};

#endif // PAGE_ENTITY_H
