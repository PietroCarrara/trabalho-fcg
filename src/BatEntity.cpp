#include "BatEntity.h"

#include <utilities.h>
#include <cmath>

#include "matrices.hpp"

BatEntity::BatEntity(float d, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) : ObjEntity("../../assets/objects/bat/model.obj") {
  this->bezier = new CubicBezier(d, p1, p2, p3, p4, true);
  this->rotation.x = deg2rad(90);
}

BatEntity::~BatEntity() {
  delete this->bezier;
}

void BatEntity::update(float dt) {
  this->bezier->update(dt);
  this->position = this->bezier->getPoint();
}