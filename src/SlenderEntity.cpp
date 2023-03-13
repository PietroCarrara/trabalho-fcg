#include "SlenderEntity.h"

#include <glm/vec3.hpp>
#include <cstdlib>
#include <cmath>
#include <cstdio>

#define deg2rad(x) ((x)/57.2958f)
#define rad2deg(x) ((x)*57.2958f)

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

    if (this->timeStanding > 5) {
        glm::vec4 playerView = this->player->getViewVec();
        float playerAngle = rad2deg(atan2(playerView.z, playerView.x));
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

}
