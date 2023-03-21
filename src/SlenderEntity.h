#ifndef SLENDERENTITY_H
#define SLENDERENTITY_H

#include "ObjEntity.h"
#include "Player.h"

class SlenderEntity : public ObjEntity
{
private:
    float timeStanding = 0;
    Player* player;

public:
    SlenderEntity(Player* p);

    void update(float dt);
};

#endif // SLENDERENTITY_H
