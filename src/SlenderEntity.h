#ifndef SLENDERENTITY_H
#define SLENDERENTITY_H

#include <glm/vec3.hpp>

#include "AudioManager.h"
#include "ObjEntity.h"
#include "Player.h"

class SlenderEntity : public ObjEntity
{
private:
    float damagePerSecond;
    int maxDist;
    int level = 0;
    float timeStanding = 0;
    Player* player;
    Sound* scary;
    Sound* camStatic;
    Sound* music1;
    Sound* music2;
    Sound* music3;
    Sound* music4;
    glm::vec3 lastSeenPos; // Last position the player saw slendeman

    bool isPlayerLookingAtPosition(glm::vec3 pos);
    void teleport();

public:
    SlenderEntity(Player* p);
    ~SlenderEntity();

    void levelUp();

    void update(float dt);
    void draw(Camera *c);
};

#endif // SLENDERENTITY_H
