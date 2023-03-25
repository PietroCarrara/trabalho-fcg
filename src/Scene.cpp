#include "Scene.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    for (Entity* e : this->entities) {
        delete e;
    }
}

Scene* Scene::update(float dt)
{
    for (Entity* e : this->entities) {
        if (!e->paused) {
            e->update(dt);
        }
    }
    return this;
}

void Scene::draw()
{
    for (Entity* e : this->entities) {
        e->draw(this->camera);
    }
}

void Scene::removeEntity(Entity* e) {
    this->entities.remove(e);
    delete e;
}
