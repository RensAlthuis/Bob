#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 normal;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 projection_matrix = mat4(1.0);
uniform vec3 directionallight = vec3(0, 0, -1);

out vec3 fragPos;
out float angle;
void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * pos;
    angle = acos(dot(normal.xyz, -directionallight));
    fragPos = (model_matrix * pos).xyz;
}