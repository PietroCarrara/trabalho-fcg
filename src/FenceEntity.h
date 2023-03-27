#ifndef FENCEENTITY_H
#define FENCEENTITY_H

#include "ObjEntity.h"
#include "CollisionManager.h"
#include "MainGameScene.h"


class FenceEntity : public ObjEntity
{
    public:
        FenceEntity(MainGameScene *s);
        std::vector<HitBox*> hitboxes;

    protected:

    private:
};

#endif // FENCEENTITY_H
