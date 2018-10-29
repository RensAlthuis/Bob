#macro INSERTVERSION
#macro CODE
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
out vec2 TexCoords;
void main()
{

    TexCoords = tex;
    gl_Position = vec4(position, 1);
}