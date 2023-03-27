#include "BushEntity.h"

#include <utilities.h>
#include <glm/vec3.hpp>

ObjEntity* BushEntity::bush = nullptr;

BushEntity::BushEntity(glm::vec3 position) {
    // Load model to be used for all pages
    if (bush == nullptr) {
        bush = new ObjEntity("../../assets/objects/bush/jungle_bush01.obj");
        bush->scale = glm::vec3(0.01);
    }
    this->position = position;
}

void BushEntity::update(float delta) {

}

// Each bush uses the single loaded model to draw itself
void BushEntity::draw(Camera* c) {
    bush->position = this->position;
    bush->draw(c);
}
