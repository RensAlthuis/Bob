#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 uvCoord;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 projection_matrix = mat4(1.0);

out vec3 fragPos;
out vec2 texCoord;
void main()
{
	texCoord = uvCoord;
    gl_Position = projection_matrix * view_matrix * model_matrix * pos;
    fragPos = (model_matrix * pos).xyz;
}