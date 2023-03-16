#include "SlenderEntity.h"

#include <glm/vec3.hpp>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <utils.h>

#include "GraphicsManager.hpp"

SlenderEntity::SlenderEntity(Player* p) : ObjEntity("../../assets/objects/slender/slender.obj")
{
    this->position = glm::vec3(10, 0, 10);
    this->player = p;
}

SlenderEntity::~SlenderEntity()
{
    //dtor
}

float angleBetween(
     glm::vec3 a,
     glm::vec3 b,
     glm::vec3 origin
){
     glm::vec3 da=glm::normalize(a-origin);
     glm::vec3 db=glm::normalize(b-origin);
     return glm::acos(glm::dot(da, db));
}

void SlenderEntity::update(float dt)
{
    this->timeStanding += dt;

    const glm::vec4 playerView = this->player->getViewVec();
    const float playerAngle = rad2deg(atan2(playerView.z, playerView.x));

    glm::vec3 fromPlayerToSlender = this->position - this->player->position;
    fromPlayerToSlender.y = playerView.y; // Put both vectors on the same Y plane
    const float angleSlenderPlayer = rad2deg(angleBetween(fromPlayerToSlender, playerView, glm::vec3(0, 0, 0)));
    const bool looking = angleSlenderPlayer < 33;

    if (!looking && this->timeStanding > 5) {
        // Teleport my man slender close to the player
        float minAngle = 90 + playerAngle;

        float angle = deg2rad(rand() % 180 + minAngle);
        float radius = rand() % 10 + 10;

        this->position.x = this->player->position.x + cos(angle) * radius;
        this->position.z = this->player->position.z + sin(angle) * radius;

        this->timeStanding = 0;

        float x2 = this->position.x;
        float y2 = this->position.z;
        float x1 = this->player->position.x;
        float y1 = this->player->position.z;
        this->rotation.y = -atan2(y2 - y1, x2 - x1);
    }

    if (looking) {
        player->sanity -= dt;
    } else {
        player->sanity += dt;
    }

    if (player->sanity < 0) {
        player->sanity = 0;
    } else if (player->sanity > 1) {
        player->sanity = 1;
    }
    GraphicsManager::setNoisiness(1 - player->sanity);
}
