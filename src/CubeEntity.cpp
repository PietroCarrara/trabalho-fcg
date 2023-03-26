#include "CubeEntity.h"

#include <cstdio>

ObjEntity* CubeEntity::cube;

CubeEntity::CubeEntity(glm::vec3 position, float width, float height, float depth)
{
    this->position = position;
    this->width = width;
    this->height = height;
    this->depth = depth;

    if (cube == nullptr) {
        cube = new ObjEntity("../../assets/objects/cube/Cube.obj");
    }
}

void CubeEntity::draw(Camera *c) {
    cube->scale = glm::vec3(this->width, this->height, this->depth);
    cube->position = this->position;
    cube->rotation = glm::vec3(0);

    cube->draw(c);
}
