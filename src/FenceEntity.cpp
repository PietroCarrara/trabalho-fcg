#include "FenceEntity.h"
#include "CubeEntity.h"

FenceEntity::FenceEntity(MainGameScene *s) : ObjEntity("../../assets/objects/fence/Fence.obj")
{
    this->scale = glm::vec3(0.1);
    this->position = glm::vec3(-3.5,0,32.7);

    glm::vec3 bboxMin = this->bboxMin[0] * this->scale;
    glm::vec3 bboxMax = this->bboxMax[0] * this->scale;

    const float width  = 30 * this->scale.x;
    const float height = bboxMax.y - bboxMin.y;
    const float depth = 5 * this->scale.z;
    const glm::vec3 center = this->position + glm::vec3(0, height/2, 0);

    // Debug cube for visualization
    // CubeEntity* cube = s->addEntity(new CubeEntity(center, width, height, depth));

    HitBox* hb = new HitBox(
      center + glm::vec3(width, height, depth) * -0.5f,
      center + glm::vec3(width, height, depth) * 0.5f
    );
    this->hitboxes.push_back(hb);
    CollisionManager::registerWall(hb);
}
