#ifndef DOORENTITY_H
#define DOORENTITY_H

#include "ObjEntity.h"
#include "CollisionManager.h"
#include "Player.h"


class DoorEntity : public ObjEntity
{
public:
    Player *player;

    HitSphere* hitZone;

    bool isOpening;
    bool isClosing;
    float progression;

    DoorEntity(Player *p);

    void update(float deltaTime);
    void interact();
};

#endif // DOORENTITY_H
