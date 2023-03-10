#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity, public FreeCamera
{
public:
    Player();

    void update(float deltaTime);
    void draw(Camera* c);
};

#endif // PLAYER_H
