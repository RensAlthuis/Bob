#version 330 core

#define nLights 8
uniform int dirLightCount;
uniform vec4 dirLightPos[nLights];
uniform float dirLightIntensity[nLights];
uniform vec3 dirLightColour[nLights];

uniform int pointLightCount;
uniform vec4 pointLightPos[nLights];
uniform vec3 pointLightAttenuation[nLights];
uniform float pointLightIntensity[nLights];
uniform vec3 pointLightColour[nLights];

uniform int spotLightCount;
uniform vec4 spotLightPos[nLights];
uniform float spotLightIntensity[nLights];
uniform vec3 spotLightAttenuation[nLights];
uniform vec3 spotLightDir[nLights];
uniform float spotLightAngle[nLights];
uniform float spotLightExponent[nLights];
uniform vec3 spotLightColour[nLights];

uniform vec3 matEmissiveColour;
uniform vec3 matAmbiantColour;
uniform vec4 matDiffuseColour;
uniform vec3 matSpecularColour;
uniform float matSpecularExp;
uniform vec3 lightAmbDiffSpec;

struct lightValue{
    vec3 L;
    float I;
};

lightValue computeDirLight(in int i){
    lightValue v;
    v.L = dirLightPos[i].xyz;
    v.I = dirLightIntensity[i];
    return v;
}

lightValue computePointLight(in vec4 surfacePos, in int i){
    lightValue v;
    v.L = pointLightPos[i].xyz - surfacePos.xyz;
    float dist = length(v.L);
    v.L = v.L / dist;

    v.I = pointLightIntensity[i] /
            dot(pointLightAttenuation[i], vec3(1.0, dist, dist*dist));
    return v;
}

lightValue computeSpotLight(in vec4 surfacePos, in int i){
    lightValue v;
    v.L = pointLightPos[i].xyz - surfacePos.xyz;
    float dist = length(v.L);
    v.L = v.L / dist;

    float distAttenuation = dot(spotLightAttenuation[i], vec3(1.0, dist, dist*dist));
    float spotAttenuation = dot(-spotLightDir[i], v.L);
    spotAttenuation = (spotAttenuation > spotLightAngle[i])
                        ? pow(spotAttenuation, spotLightExponent[i])
                        : 0.0;
    v.I = spotLightIntensity[i] * spotAttenuation / distAttenuation;
    return v;
}

vec3 computeAmb(in lightValue lv, in int i){
    return lv.I * (pointLightColour[i] * lightAmbDiffSpec.x) * matAmbiantColour;
}

vec3 computeDiff(in vec3 norm, in lightValue lv, in int i){
    return lv.I * (pointLightColour[i] * lightAmbDiffSpec.y)
                * matDiffuseColour.rgb
                * max(0.0, dot(norm, lv.L));
}

vec3 computeSpec(in vec3 norm, in vec4 pos, in lightValue lv, in int i){
    vec3 viewVec = normalize(-pos.xyz);
    vec3 reflection = 2.0 * dot(lv.L, norm) * norm - lv.L;
    return (dot(norm, lv.L) <= 0.0)
            ? vec3(0,0,0)
            : (lv.I * (pointLightColour[i] * lightAmbDiffSpec.z)
                    * matSpecularColour
                    * pow(max(0.0, dot(reflection, viewVec)), matSpecularExp));
}

vec3 computefinalColour(in lightValue lv, in vec4 pos, in vec3 norm, in int i){
    return computeAmb(lv, i)
         + computeDiff(norm, lv, i)
         + computeSpec(norm, pos, lv, i);
}

in vec4 surfacepos;
in vec3 surfacenorm;
out vec4 FragColor;
void main()
{
    int i;
    vec4 finalColour;
    finalColour.rgb = matEmissiveColour;
    finalColour.a = matDiffuseColour.a;
    for (i = 0; i < pointLightCount; i++){
        lightValue lv = computePointLight(surfacepos, i);
        finalColour.rgb += computefinalColour(lv, surfacepos, surfacenorm, i);
    }
    FragColor = finalColour;
}