#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform vec4 lightCol;
uniform vec3 lightPos;
uniform sampler2D tex;
in vec3 fragPos;
void main()
{
    float intensity = 1/ length(fragPos - lightPos);
    FragColor = texture(tex, texCoord) * intensity * lightCol;
}