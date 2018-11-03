#include "Object.h"
#include "Component.h"
namespace Engine
{
Object::Object() : translation(0, 0, 0),
                   scaling(1, 1, 1),
                   rotation(1, 0, 0, 0),
                   children(),
                   parent(nullptr)
{
    transform = Maths::Matrix4::identity();
    recalculate();
}

void Object::recalculate()
{
    transform = Maths::Matrix4::scale(scaling.x, scaling.y, scaling.z) *
                Maths::Matrix4::rotate(rotation) *
                Maths::Matrix4::translate(translation) *
                (parent == nullptr ? Maths::Matrix4::identity() : parent->Transform());
    for (Object *p : children)
    {
        p->recalculate();
    }
}

const Maths::Matrix4 &Object::Transform() const
{
    return transform;
}

const Maths::Vector3 Object::Front() const
{
    return Maths::Vector3(transform[2], transform[6], transform[10]);
}

void Object::translate(Maths::Vector3 v, bool inWorldSpace)
{
    if (inWorldSpace)
    {
        translation = translation + v;
    }
    else
    {
        Maths::Vector3 v2 = v.rotate(rotation);
        translation.x += v2.x;
        translation.y += v2.y;
        translation.z += v2.z;
    }
    recalculate();
}

void Object::translate(float x, float y, float z, bool inWorldSpace)
{
    translate(Maths::Vector3(x, y, z), inWorldSpace);
}

void Object::rotate(Maths::Quaternion q)
{
    rotation = q * rotation;
    recalculate();
}

void Object::lookAt(const Maths::Vector3 &v)
{

    Maths::Vector3 dir = (v - translation).normalize();
    float anglefront = atan2f(Maths::Vector3::Forward.x, Maths::Vector3::Forward.z);
    float angledir = atan2f(dir.x, dir.z);

    float xangle = (anglefront - angledir) * (180.0f / (float)M_PI);
    float a = acosf(dir.dot(Maths::Vector3::Up));
    float yangle = ((float)M_PI_2 - a) * (180.0f / (float)M_PI);

    Maths::Quaternion swing(Maths::Quaternion::fromAxisAngle(-xangle, Maths::Vector3::Up));
    Maths::Quaternion tilt(Maths::Quaternion::fromAxisAngle(yangle,
                                                            Maths::Vector3::Right.rotate(swing)));

    rotation = tilt * swing;
    recalculate();
}

void Object::scale(Maths::Vector3 s)
{
    scaling = s;
    recalculate();
}

void Object::update()
{
    for (int i = 0; i < components.size(); i++)
    {
        components.at(i)->update();
    }
}

void Object::addChild(Object *object)
{
    children.push_back(object);
    object->parent = this;
    recalculate();
}

void Object::addComponent(Component *component)
{
    component->parent = this;
    components.push_back(component);
}

Object::~Object()
{
    for (auto p : children)
    {
        delete p;
    }

    for (int i = 0; i < components.size(); i++)
    {
        delete components.at(i);
    }
}
}; // namespace Engine
