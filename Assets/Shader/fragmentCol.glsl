#version 330 core
out vec4 FragColor;

uniform vec4 lightCol;
uniform vec3 lightPos;
uniform vec4 colour;
in vec3 fragPos;
void main()
{
    float intensity = 1/ length(fragPos - lightPos);
    FragColor =  colour * intensity * lightCol;
}