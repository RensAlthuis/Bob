#include "Scene.h"

namespace Engine
{

void Scene::addChild(Object *object)
{
    children.push_back(object);
}

void Scene::setLights()
{

}

void Scene::update()
{
    for(Object* p : children){
        p->update();
    }
}

}; // namespace Engine