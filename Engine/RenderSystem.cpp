#include "RenderSystem.h"

namespace Engine
{

RenderSystem::RenderSystem() : System()
{
    addComponentType(TransformComponent::TYPE);
    addComponentType(RenderComponent::TYPE);
    addComponentType(ModelComponent::TYPE);
}

void RenderSystem::update(float deltaTime, ECS::IComponent **components) const
{
    //transform
    TransformComponent *transform = (TransformComponent *)components[0];
    RenderComponent *render = (RenderComponent *)components[1];
    ModelComponent *model = (ModelComponent *)components[2];

    model->model->bind();
    render->shader->setMat4("model_matrix", transform->transform.Matrix());
    setMaterial(render);
    glDrawElements(GL_TRIANGLES, model->model->ElementCount(), GL_UNSIGNED_INT, 0);
}

void RenderSystem::setMaterial(RenderComponent *render) const
{
    Shader *shader = render->shader;
    Material *mat = render->mat;
    shader->setVec3("matEmissiveColour", mat->mEC);
    shader->setVec3("matAmbiantColour", mat->mAC);
    shader->setVec3("matDiffuseColour", Maths::Vector3(mat->mDC.x, mat->mDC.y, mat->mDC.z));
    shader->setVec3("matSpecularColour", mat->mSC);
    shader->setFloat("matSpecularExp", mat->mSE);
    shader->setVec3("lightAmbDiffSpec", mat->lADS);
}
}; // namespace Engine