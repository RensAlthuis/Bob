#macro INSERTVERSION
#macro CODE

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 normal;

uniform mat4 model_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 proj_matrix = mat4(1.0);

void main()
{
    vec4 worldpos = model_matrix * pos;
    gl_Position = proj_matrix * view_matrix * worldpos;
}