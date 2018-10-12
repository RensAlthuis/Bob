#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 normal;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 projection_matrix = mat4(1.0);

uniform vec3 directionallight = vec3(0, 0, -1);
uniform vec3 pointlight = vec3(0,0,1);

out float directionalangle;
out float pointangle;
out vec3 point;

void main()
{
    vec4 worldpos = model_matrix * pos;
    gl_Position = projection_matrix * view_matrix * worldpos;
    directionalangle = max(0.0, dot(normal.rgb, -directionallight));
    point = worldpos.xyz - pointlight;
    pointangle = max(0.0, dot(normal.rgb, -normalize(point)));
}