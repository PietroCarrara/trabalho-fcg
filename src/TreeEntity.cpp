#include "TreeEntity.h"

#include <utilities.h>
#include <glcommon.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"

ObjEntity* TreeEntity::tree = nullptr;

TreeEntity::TreeEntity(glm::vec3 position, float tiltZ, float tiltX) {
  // Load model to be used for all pages
  if (tree == nullptr) {
    tree = new ObjEntity("../../assets/objects/tree/N64_Tree.obj");
    tree->scale = glm::vec3(0.1, 0.1, 0.1);
  }

  this->position = position;
  this->tiltZ = tiltZ;
  this->tiltX = tiltX;
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
