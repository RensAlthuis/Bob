#pragma once
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"

namespace Engine
{
class ModelRenderer : Component
{
  private:
    static Model* lastBoundModel;
    Model *model;
    Shader *shader;
    Material *material;

  public:
    ModelRenderer(Model *model, Material *material, Shader *shader);
    ~ModelRenderer();
    void update() override;
    void draw();
};
}; // namespace Engine