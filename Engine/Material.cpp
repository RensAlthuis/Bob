#include "Material.h"

namespace Engine
{

Material::Material()
    : mEC(Maths::Vector3::Zero),
      mAC(Maths::Vector3::Zero),
      mDC(Maths::Vector4::Zero),
      mSC(Maths::Vector3::Zero),
      mSE(0),
      lADS(Maths::Vector3::Zero)
{
}

Material::Material(const Maths::Vector3 EmissiveColour, const Maths::Vector3 AmbientColour, const Maths::Vector4 DiffuseColour,
                   const Maths::Vector3 SpecularColour, const float SpecularExp, const Maths::Vector3 ComponentScalars)
    : mEC(EmissiveColour), mAC(AmbientColour), mDC(DiffuseColour), mSC(SpecularColour), mSE(SpecularExp), lADS(ComponentScalars)
{
}

Material::~Material() {}
}; // namespace Engine