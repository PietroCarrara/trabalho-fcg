#ifndef SLENDERENTITY_H
#define SLENDERENTITY_H

#include <glm/vec3.hpp>

#include "AudioManager.h"
#include "ObjEntity.h"
#include "Player.h"

class SlenderEntity : public ObjEntity
{
private:
    float timeStanding = 0;
    Player* player;
    Sound* scary;
    Sound* camStatic;
    glm::vec3 lastSeenPos; // Last position the player saw slendeman

public:
    SlenderEntity(Player* p);
    ~SlenderEntity();

    void update(float dt);
};

#endif // SLENDERENTITY_H
