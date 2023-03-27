#ifndef BUSHENTITY_H
#define BUSHENTITY_H

#include "Entity.h"
#include "ObjEntity.h"

class BushEntity : public Entity
{
  private:
    static ObjEntity* bush;

    glm::vec3 position;
  public:
    BushEntity(glm::vec3 position);

    void update(float delta);
    void draw(Camera* c);
};

#endif // BUSHENTITY_H
