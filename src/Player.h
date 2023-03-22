#ifndef PLAYER_H
#define PLAYER_H

#include "AudioManager.h"
#include "Entity.h"

class Player : public Entity, public FreeCamera
{
private:
    Sound *step;

public:
    Player();
    ~Player();

    float sanity = 1;

    void update(float deltaTime);
    void draw(Camera* c);
};

#endif // PLAYER_H
