#version 330

in vec2 UVcoords; // coordinates of fragment

uniform sampler2D tex; // corresponding to .c file, must have same name. Can also be 3D if adjusted.

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main()
{
    // Read color at UVcoords position in the texture
    vec4 TexColor = texture2D(tex, UVcoords);
    FragColor = TexColor;
    // default bright color to black
    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
