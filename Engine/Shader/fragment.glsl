#version 330 core
out vec4 FragColor;

uniform vec4 col;
uniform vec2 mouse;

in vec2 light;
void main()
{
    float intensity = 1/ length(light - mouse);
    FragColor = col * intensity;
}