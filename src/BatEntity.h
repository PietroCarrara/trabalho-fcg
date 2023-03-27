#ifndef RAT_ENTITY_H
#define RAT_ENTITY_H

#include <glm/vec3.hpp>

#include "ObjEntity.h"
#include "CubicBezier.h"

class BatEntity : public ObjEntity {
  private:
    CubicBezier *bezier;

  public:
    BatEntity(float duration, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
    ~BatEntity();

    void update(float dt);
};

#endif
