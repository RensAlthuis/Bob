#include "ModelRenderer.h"
namespace Engine
{

Model *ModelRenderer::lastBoundModel = nullptr;

ModelRenderer::ModelRenderer(Model *model, Material *material, Shader *shader)
    : Component(), model(model), material(material), shader(shader)
{
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::update()
{
    draw();
}

void ModelRenderer::draw()
{
    if (lastBoundModel != model)
    {
        model->bind();
        lastBoundModel = model;
    }
    material->setShader(shader);
    shader->setMat4("model_matrix", parent->Transform());
    glDrawElements(GL_TRIANGLES, model->ElementCount(), GL_UNSIGNED_INT, 0);
}

}; // namespace Engine