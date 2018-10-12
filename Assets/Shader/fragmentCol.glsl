#version 330 core
out vec4 FragColor;

uniform vec4 lightCol;
uniform vec4 colour;
uniform float pointIntensity = 0;

in float directionalangle;
in float pointangle;
in vec3 point;

void main()
{
    float pointDistance = 1/length(point);
    FragColor = 0.1+(colour*directionalangle*lightCol)
                    +(pointIntensity*pointDistance*colour*pointangle);
}