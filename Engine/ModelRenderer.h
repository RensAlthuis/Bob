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
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Material> material;

  public:
    ModelRenderer(Model &model, Material &material, Shader &shader);
    ~ModelRenderer();
    void update() override;
    void draw();
};
}; // namespace Engine