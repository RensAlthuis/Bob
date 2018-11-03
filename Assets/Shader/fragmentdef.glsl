#macro INSERTVERSION
#macro CODE
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gEm;
layout (location = 3) out vec3 gAmb;
layout (location = 4) out vec3 gDiff;
layout (location = 5) out vec4 gSpec;
layout (location = 6) out vec3 gADS;
uniform vec3 matEmissiveColour;
uniform vec3 matAmbiantColour;
uniform vec3 matDiffuseColour;
uniform vec3 matSpecularColour;
uniform float matSpecularExp;
uniform vec3 lightAmbDiffSpec;

in vec3 surfacenorm;
in vec3 surfacepos;

void main()
{
    gPosition = surfacepos;
    gNormal = normalize(surfacenorm);
    gAmb = matAmbiantColour;
    gDiff = matDiffuseColour;
    gSpec.rgb = matSpecularColour.rgb;
    gSpec.a = matSpecularExp;
    gEm = matEmissiveColour;
    gADS = lightAmbDiffSpec;
}