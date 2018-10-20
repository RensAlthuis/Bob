#pragma once
#include "Shader.h"
#include "Maths/Maths.h"

namespace Engine
{

class Material {

    private:
        Maths::Vector3 mEC;
        Maths::Vector3 mAC;
        Maths::Vector4 mDC;
        Maths::Vector3 mSC;
        Maths::Vector3 lADS;
        float mSE;

    public:
        Material();
        Material( const Maths::Vector3 EmissiveColour,
                    const Maths::Vector3 AmbientColour,
                    const Maths::Vector4 DiffuseColour,
                    const Maths::Vector3 SpecularColour,
                    const float SpecularExp,
                    const Maths::Vector3 ComponentScalars);
        ~Material();
        void setShader(Shader* shader) const;

};

};