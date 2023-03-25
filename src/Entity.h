#ifndef ENTITY_H
#define ENTITY_H

#include "Camera.hpp"

class Entity
{
public:
    bool paused = false;

    virtual ~Entity();
    virtual void update(float deltaTime);
    virtual void draw(Camera* c);
};

#endif // ENTITY_H
