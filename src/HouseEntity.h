#ifndef HOUSEENTITY_H
#define HOUSEENTITY_H

#include "ObjEntity.h"
#include "CollisionManager.h"
#include "MainGameScene.h"
#include "Player.h"


class HouseEntity : public ObjEntity
{
    public:
        HouseEntity(MainGameScene *s);
        std::vector<HitBox*> hitboxes;
};

#endif // HOUSEENTITY_H
