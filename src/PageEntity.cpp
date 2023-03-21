#include "PageEntity.h"

#include <utilities.h>
#include <glcommon.h>
#include <glm/vec3.hpp>

#include "InputManager.hpp"

ObjEntity* PageEntity::page = nullptr;

PageEntity::PageEntity(glm::vec3 position, float rotation)
{
    // Load model to be used for all pages
    if (page == nullptr) {
        page = new ObjEntity("../../assets/objects/pages/page1.obj");
        page->rotation.z = deg2rad(90);
    }

    this->position = position;
    this->rotation = rotation;
}


void PageEntity::update(float delta) {
    this->rotation += delta;
}

// Each page uses the single loaded model to draw itself
void PageEntity::draw(Camera* c) {
    page->position = this->position;
    page->rotation.y = this->rotation;
    page->draw(c);
}
