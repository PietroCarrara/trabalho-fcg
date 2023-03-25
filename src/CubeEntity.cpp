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

    printf("<%f, %f, %f> {%f, %f, %f}\n", position.x, position.y, position.z, width, height, depth);
}

void CubeEntity::draw(Camera *c) {
    cube->scale = glm::vec3(width, height, depth);
    cube->position = position;
    cube->rotation = glm::vec3(0);

    cube->draw(c);
}
