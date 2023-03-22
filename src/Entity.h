#ifndef ENTITY_H
#define ENTITY_H

#include "Camera.hpp"

class Entity
{
public:
    virtual ~Entity();
    virtual void update(float deltaTime) = 0;
    virtual void draw(Camera* c) = 0;
};

#endif // ENTITY_H
