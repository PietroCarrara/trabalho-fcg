#ifndef PAGE_ENTITY_H
#define PAGE_ENTITY_H

#include <string>

#include <glm/vec3.hpp>

#include "ObjEntity.h"
#include "Camera.hpp"
#include "CollisionManager.h"

class PageEntity : public ObjEntity
{
    public:
        PageEntity(glm::vec3 position, std::string name = "page1");
        ~PageEntity();

        HitSphere* hitZone;

        void update(float delta);
};

#endif // PAGE_ENTITY_H
