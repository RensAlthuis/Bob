#version 330 core

layout (location = 0) in vec4 pos;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 projection_matrix = mat4(1.0);

out vec2 light;
void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * pos;
    light = (projection_matrix * model_matrix * pos).xy;
}