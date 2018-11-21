#include "ModelRenderer.h"
namespace Engine
{

ModelRenderer::ModelRenderer(Model &model, Material &material, Shader &shader)
    : Component(), model(&model), material(&material), shader(&shader)
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
    model->bind();
    // material->setShader(*shader);
    shader->setMat4("model_matrix", parent->Transform());
    glDrawElements(GL_TRIANGLES, model->ElementCount(), GL_UNSIGNED_INT, 0);
}

}; // namespace Engine