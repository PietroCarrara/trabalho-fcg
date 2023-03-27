#include "HouseEntity.h"

#include <utilities.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"
#include "CubeEntity.h"

HouseEntity::HouseEntity(MainGameScene *s) : ObjEntity("../../assets/objects/house/house8.obj")
{
    this->scale = glm::vec3(0.012);
    this->position = glm::vec3(0,0,30);
    this->rotation.y = M_PI;

    glm::vec3 bboxMin = this->bboxMin[0] * this->scale;
    glm::vec3 bboxMax = this->bboxMax[0] * this->scale;

    const float width  = 450 * this->scale.x;
    const float height = bboxMax.y - bboxMin.y;
    const float depth = 600 * this->scale.z;
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

