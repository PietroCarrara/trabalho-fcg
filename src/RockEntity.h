#ifndef ROCKENTITY_H
#define ROCKENTITY_H

#include "Entity.h"
#include "ObjEntity.h"
#include "MainGameScene.h"
#include "CollisionManager.h"

class RockEntity : public Entity
{
private:
    static ObjEntity* rock;
    glm::vec3 position;

    std::vector<HitBox*> hitboxes;
public:
    RockEntity(MainGameScene *s, glm::vec3 position);

    void update(float delta);
    void draw(Camera* c);
};

#endif // ROCKENTITY_H
