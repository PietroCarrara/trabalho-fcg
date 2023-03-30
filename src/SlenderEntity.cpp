#include "SlenderEntity.h"

#include <glm/vec3.hpp>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <utilities.h>

#include "GraphicsManager.hpp"
#include "CollisionManager.h"

#define DAMAGE_PER_SECOND 0.33
#define HEAL_PER_SECOND 1

SlenderEntity::SlenderEntity(Player* p) : ObjEntity("../../assets/objects/slender/slender.obj")
{
    this->scary = AudioManager::makeSound("../../assets/audio/dramatic-piano.wav");
    this->music1 = AudioManager::makeSound("../../assets/audio/music1.wav", true);
    this->music2 = AudioManager::makeSound("../../assets/audio/music2.wav", true);
    this->music3 = AudioManager::makeSound("../../assets/audio/music3.wav", true);
    this->music4 = AudioManager::makeSound("../../assets/audio/music4.wav", true);
    this->camStatic = AudioManager::makeSound("../../assets/audio/static.wav", true, 0);
    AudioManager::playSound(this->camStatic);

    this->position = glm::vec3(10, 0, 10);
    this->player = p;
}

SlenderEntity::~SlenderEntity() {
    AudioManager::destroySound(this->scary);
    AudioManager::destroySound(this->camStatic);
    AudioManager::destroySound(this->music1);
    AudioManager::destroySound(this->music2);
    AudioManager::destroySound(this->music3);
    AudioManager::destroySound(this->music4);
}

void SlenderEntity::levelUp() {
    this->level++;

    switch(this->level) {
    case 1:
        this->teleport();
        this->damagePerSecond = 0.33;
        this->maxDist = 20;
        AudioManager::playSound(this->music1);
        break;
    case 2:
        this->damagePerSecond = 0.5;
        this->maxDist = 17;
        AudioManager::playSound(this->music2);
        break;
    case 3:
        this->maxDist = 14;
        this->damagePerSecond = 0.75;
        AudioManager::playSound(this->music3);
        break;
    case 4:
        this->damagePerSecond = 1;
        this->maxDist = 11;
        AudioManager::playSound(this->music4);
        break;
    default:
        this->level = 4;
        break;
    }
}

void SlenderEntity::update(float dt)
{
    if (this->level <= 0) {
        return;
    }
    this->timeStanding += dt;

    const float distance = glm::length(this->position - this->player->position);

    bool looking = this->isPlayerLookingAtPosition(this->position);

    // Teleport
    if (this->timeStanding >= 5 && !looking) {
        teleport();
    }

    if (looking) {
        // Check for jumpscare
        if (lastSeenPos != this->position && distance <= 15) {
            AudioManager::playSound(this->scary);
        }

        this->timeStanding = 0;
        lastSeenPos = this->position;
        player->sanity -= dt * this->damagePerSecond;
    } else {
        player->sanity += dt * HEAL_PER_SECOND;
    }

    if (player->sanity < 0) {
        player->sanity = 0;
    } else if (player->sanity > 1) {
        player->sanity = 1;
    }

    // Play the static sound, increasing at a quadratic rate
    float volume = 1 - this->player->sanity;
    AudioManager::setSoundVolume(this->camStatic, volume*volume);

    // Look at player
    float x2 = this->position.x;
    float y2 = this->position.z;
    float x1 = this->player->position.x;
    float y1 = this->player->position.z;
    this->rotation.y = -atan2(y2 - y1, x2 - x1);
}

bool SlenderEntity::isPlayerLookingAtPosition(glm::vec3 position) {
    const glm::vec4 playerView = this->player->getViewVec();
    // const float playerAngle = rad2deg(atan2(playerView.z, playerView.x));

    glm::vec3 fromPlayerToSlender = position - this->player->position;
    fromPlayerToSlender.y = 0; // Put both vectors on the same Y plane
    const float distance = glm::length(fromPlayerToSlender);

    const float angleSlenderPlayer = rad2deg(angleBetween(fromPlayerToSlender, (glm::vec3)playerView));

    return angleSlenderPlayer < 33 && distance < 60 && !CollisionManager::hitsWall(this->player->position, fromPlayerToSlender);;
}

void SlenderEntity::teleport() {
    while (true) {
        float angle = deg2rad(randomFloat(360));
        float radius = rand() % this->maxDist + 2;
        const glm::vec3 newPos(this->player->position.x + cos(angle) * radius, 0, this->player->position.z + sin(angle) * radius);

        if (!this->isPlayerLookingAtPosition(newPos)) {
            this->timeStanding = 0;
            this->position = newPos;
            return;
        }
    }
}

void SlenderEntity::draw(Camera *c) {
    if (this->level <= 0) {
        return;
    }
    ObjEntity::draw(c);
}
