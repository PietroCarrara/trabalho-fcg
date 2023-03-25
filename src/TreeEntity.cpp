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
    glm::vec3 bboxMin = tree->bboxMin[i] * tree->scale;
    glm::vec3 bboxMax = tree->bboxMax[i] * tree->scale;

    const float width  = 13 * tree->scale.x; // measured directly from the obj file
    const float height = bboxMax.y - bboxMin.y;
    const float depth = 13 * tree->scale.z; // measured directly from the obj file

    // Debug cube for visualization
    CubeEntity* cube = s->addEntity(new CubeEntity(position + glm::vec3(0, height/2, 0), width, height, depth));

    HitBox hb(
      cube->position + glm::vec3(cube->width, cube->height, cube->depth) * -0.5f,
      cube->position + glm::vec3(cube->width, cube->height, cube->depth) * 0.5f
    );
    this->hitboxes.push_back(hb);
    CollisionManager::registerWall(hb);
  }
}

void TreeEntity::update(float delta) {

}

// Each page uses the single loaded model to draw itself
void TreeEntity::draw(Camera* c) {
  tree->position = this->position;
  tree->rotation.z = this->tiltZ;
  tree->rotation.x = this->tiltX;
  tree->draw(c);
}
