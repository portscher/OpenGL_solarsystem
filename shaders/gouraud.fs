#version 330

in vec4 vColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main()
{
    FragColor = vColor;
    // grouraud has no bloom support
    // default bright color to black
    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
