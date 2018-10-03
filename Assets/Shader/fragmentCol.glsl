#version 330 core
out vec4 FragColor;

uniform vec4 lightCol;
uniform vec3 lightPos;
uniform vec4 colour;
flat in vec3 col;
in float angle;
void main()
{
    // float intensity = 1/ length(fragPos - lightPos);
    // FragColor = vec4(col.rgb, 1);
    FragColor = 0.1+colour*angle*lightCol;
}