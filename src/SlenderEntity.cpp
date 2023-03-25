#include "SlenderEntity.h"

#include <glm/vec3.hpp>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <utilities.h>

#include "GraphicsManager.hpp"

#define DAMAGE_PER_SECOND 0.33
#define HEAL_PER_SECOND 1


SlenderEntity::SlenderEntity(Player* p) : ObjEntity("../../assets/objects/slender/slender.obj")
{
    this->scary = AudioManager::makeSound("../../assets/audio/dramatic-piano.wav");
    this->position = glm::vec3(10, 0, 10);
    this->player = p;
}

SlenderEntity::~SlenderEntity() {
    AudioManager::destroySound(this->scary);
}

void SlenderEntity::update(float dt)
{
    this->timeStanding += dt;

    const glm::vec4 playerView = this->player->getViewVec();
    const float playerAngle = rad2deg(atan2(playerView.z, playerView.x));

    glm::vec3 fromPlayerToSlender = this->position - this->player->position;
    fromPlayerToSlender.y = playerView.y; // Put both vectors on the same Y plane
    const float distance = glm::length(fromPlayerToSlender);

    const float angleSlenderPlayer = rad2deg(angleBetween(fromPlayerToSlender, (glm::vec3)playerView));
    const bool looking = angleSlenderPlayer < 33 && distance < 60;

    if (!looking && this->timeStanding > 5) {
        // Teleport my man slender close to the player
        float minAngle = 90 + playerAngle;

        float angle = deg2rad(rand() % 180 + minAngle);
        float radius = rand() % 20 + 2;

        this->position.x = this->player->position.x + cos(angle) * radius;
        this->position.z = this->player->position.z + sin(angle) * radius;

        this->timeStanding = 0;
    }

    if (looking) {
        // Check for jumpscare
        if (lastSeenPos != this->position && distance <= 15) {
            AudioManager::playSound(this->scary);
        }
        lastSeenPos = this->position;
        player->sanity -= dt * DAMAGE_PER_SECOND;
    } else {
        player->sanity += dt * HEAL_PER_SECOND;
    }

    if (player->sanity < 0) {
        player->sanity = 0;
    } else if (player->sanity > 1) {
        player->sanity = 1;
    }
    GraphicsManager::setNoisiness(1 - player->sanity);

    // Look at player
    float x2 = this->position.x;
    float y2 = this->position.z;
    float x1 = this->player->position.x;
    float y1 = this->player->position.z;
    this->rotation.y = -atan2(y2 - y1, x2 - x1);
}
