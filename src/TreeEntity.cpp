#include "TreeEntity.h"

#include <utilities.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"
#include "CubeEntity.h"

ObjEntity* TreeEntity::tree = nullptr;

TreeEntity::TreeEntity(MainGameScene *s, glm::vec3 position, float tiltZ, float tiltX) {
  // Load model to be used for all pages
  if (tree == nullptr) {
    tree = new ObjEntity("../../assets/objects/tree/N64_Tree.obj");
    tree->scale = glm::vec3(0.1, 0.1, 0.1);
  }

  this->position = position;
  this->tiltZ = tiltZ;
  this->tiltX = tiltX;

  for (unsigned int i = 0; i < tree->bboxMax.size(); i++) {
    glm::vec3 bboxMin = tree->bboxMin[i];
    glm::vec3 bboxMax = tree->bboxMax[i];

    const float width  = 13 * tree->scale.x; // measured directly from the obj file
    const float height = (bboxMax.y - bboxMin.y) * tree->scale.y;
    const float depth = 13 * tree->scale.z; // measured directly from the obj file
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
}

TreeEntity::~TreeEntity() {
  for (HitBox *b : this->hitboxes) {
    CollisionManager::deregisterWall(b);
    delete b;
  }
}

// Each page uses the single loaded model to draw itself
void TreeEntity::draw(Camera* c) {
  tree->position = this->position;
  tree->rotation.z = this->tiltZ;
  tree->rotation.x = this->tiltX;
  tree->draw(c);
}
