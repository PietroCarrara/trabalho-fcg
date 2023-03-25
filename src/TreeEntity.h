#ifndef TREE_ENTITY_H
#define TREE_ENTITY_H

#include <vector>

#include "Entity.h"
#include "ObjEntity.h"
#include "MainGameScene.h"
#include "CollisionManager.h"

class TreeEntity : public Entity {
  private:
    static ObjEntity* tree;

    glm::vec3 position;
    float tiltZ, tiltX;

    std::vector<HitBox*> hitboxes;

  public:
    TreeEntity(MainGameScene *s, glm::vec3 position, float tiltZ, float tiltX);
    ~TreeEntity();

    void draw(Camera* c);
};

#endif
