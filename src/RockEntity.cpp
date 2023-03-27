#include "RockEntity.h"

#include <utilities.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"
#include "CubeEntity.h"

ObjEntity* RockEntity::rock = nullptr;

RockEntity::RockEntity(MainGameScene *s, glm::vec3 position) {
    // Load model to be used for all pages
    if (rock == nullptr) {
        rock = new ObjEntity("../../assets/objects/rock/Rock.obj");
        rock->scale = glm::vec3(1.5);
    }

    this->position = position;

    for (unsigned int i = 0; i < rock->bboxMax.size(); i++) {
        glm::vec3 bboxMin = rock->bboxMin[i] * rock->scale;
        glm::vec3 bboxMax = rock->bboxMax[i] * rock->scale;

        const float width  = 2.5 * rock->scale.x;
        const float height = bboxMax.y - bboxMin.y;
        const float depth = 2.5 * rock->scale.z;
        const glm::vec3 center = this->position + glm::vec3(0, height/2, 0);

        // Debug cube for visualization
        //CubeEntity* cube = s->addEntity(new CubeEntity(position + glm::vec3(0, height/2, 0), width, height, depth));

        HitBox* hb = new HitBox(
        center + glm::vec3(width, height, depth) * -0.5f,
        center + glm::vec3(width, height, depth) * 0.5f
        );
        this->hitboxes.push_back(hb);
        CollisionManager::registerWall(hb);
  }
}

void RockEntity::update(float delta) {

}

// Each rock uses the single loaded model to draw itself
void RockEntity::draw(Camera* c) {
    rock->position = this->position;
    rock->draw(c);
}
