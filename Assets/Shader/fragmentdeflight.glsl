#macro INSERTVERSION
#macro USE_LIGHTS

#macro CODE

uniform sampler2D gPos;
uniform sampler2D gNorm;
uniform sampler2D gEm;
uniform sampler2D gAmb;
uniform sampler2D gDiff;
uniform sampler2D gSpec;
uniform sampler2D gADS;

struct lightValue{
    vec3 L;
    float I;
    vec3 C;
};

lightValue computeDirLight(in int i){
    lightValue v;
    v.L = dirLightPos[i];
    v.I = dirLightIntensity[i];
    v.C = dirLightColour[i];
    return v;
}

lightValue computePointLight(in vec3 surfacePos, in int i){
    lightValue v;
    v.L = pointLightPos[i] - surfacePos;
    float dist = length(v.L);
    v.L = v.L / dist;
    v.C = pointLightColour[i];

    v.I = pointLightIntensity[i] /
            dot(pointLightAttenuation[i], vec3(1.0, dist, dist*dist));
    return v;
}

lightValue computeSpotLight(in vec3 surfacePos, in int i){
    lightValue v;
    v.C = spotLightColour[i];
    v.L = spotLightPos[i] - surfacePos;
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

vec3 computeAmb(in lightValue lv, in float scalar, in vec3 matAmbiantColour, in int i){
    return lv.I * (lv.C * scalar) * matAmbiantColour;
}

vec3 computeDiff(in vec3 norm, in lightValue lv, in float scalar, in vec3 matDiffuseColour, in int i){
    return lv.I * (lv.C * scalar)
                * matDiffuseColour
                * max(0.0, dot(norm, lv.L));
}

vec3 computeSpec(in vec3 norm, in vec3 pos, in lightValue lv, in float scalar, in vec3 matSpecularColour, in float matSpecularExp, in int i){
    vec3 viewVec = normalize(-pos);
    vec3 reflection = 2.0 * dot(lv.L, norm) * norm - lv.L;
    return (dot(norm, lv.L) <= 0.0)
            ? vec3(0,0,0)
            : (lv.I * (lv.C * scalar)
                    * matSpecularColour
                    * pow(max(0.0, dot(reflection, viewVec)), matSpecularExp));
}

vec3 computefinalColour(in lightValue lv, in vec3 pos, in vec3 norm, in vec3 ads, in vec3 matAmbColour, in vec3 matDiffColour, in vec3 matSpecColour, in float matSpecularExp, in int i){
    return computeAmb(lv, ads.x, matAmbColour, i)
         + computeDiff(norm, lv, ads.y, matDiffColour, i)
         + computeSpec(norm, pos, lv, ads.z, matSpecColour, matSpecularExp, i);
}

in vec2 TexCoords;
out vec4 FragColor;
void main()
{
    vec3 surfacepos = texture(gPos, TexCoords).rgb;
    vec3 surfacenorm = texture(gNorm, TexCoords).rgb;
    vec3 colEm= texture(gEm, TexCoords).rgb;
    vec3 colAmb = texture(gAmb, TexCoords).rgb;
    vec3 colDiff = texture(gDiff, TexCoords).rgb;
    vec3 colSpec= texture(gAmb, TexCoords).rgb;
    float expSpec= texture(gAmb, TexCoords).a;
    vec3 colADS = texture(gADS, TexCoords).rgb;

    int i;
    vec4 finalColour;
    finalColour.rgb = colEm;
    finalColour.a = 1;
    for (i = 0; i < nDirLights; i++){
        lightValue lv = computeDirLight(i);
        finalColour.rgb += computefinalColour(lv, surfacepos, surfacenorm, colADS, colAmb, colDiff, colSpec, expSpec, i);
    }
    for (i = 0; i < nPointLights; i++){
        lightValue lv = computePointLight(surfacepos, i);
        finalColour.rgb += computefinalColour(lv, surfacepos, surfacenorm, colADS, colAmb, colDiff, colSpec, expSpec, i);
    }
    for (i = 0; i < nSpotLights; i++){
        lightValue lv = computeSpotLight(surfacepos, i);
        finalColour.rgb += computefinalColour(lv, surfacepos, surfacenorm, colADS, colAmb, colDiff, colSpec, expSpec, i);
    }
    FragColor = finalColour;
    // FragColor = vec4(TexCoords,0,1);
    // FragColor = vec4(surfacepos,1);
}