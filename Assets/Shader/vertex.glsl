#version 330 core


layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 proj_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);

out vec3 surfacenorm;
out vec4 surfacepos;
void main()
{
    surfacenorm = normal.xyz;
    surfacepos = view_matrix * model_matrix * position;
    gl_Position = proj_matrix * surfacepos;
}