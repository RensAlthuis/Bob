#pragma once
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"

namespace Engine
{
class ModelRenderer : public Component
{
  private:
    Model* model; //shared objects. ModelRenderer does not need to destroy them.
    Shader* shader;
    Material* material;

  public:
    ModelRenderer(Model &model, Material &material, Shader &shader);
    ~ModelRenderer();
    void update() override;
    void draw();
};
}; // namespace Engine