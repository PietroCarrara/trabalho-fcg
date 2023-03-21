#ifndef TREE_ENTITY_H
#define TREE_ENTITY_H

#include "Entity.h"
#include "ObjEntity.h"

class TreeEntity : public Entity {
  private:
    static ObjEntity* tree;

  public:
    TreeEntity(glm::vec3 position, float tiltZ, float tiltX);

    glm::vec3 position;
    float tiltZ, tiltX;

    void update(float delta);
    void draw(Camera* c);
};

#endif