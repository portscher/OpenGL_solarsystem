#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

void main()
{
    TexCoords = aPos;
    gl_Position = ProjectionMatrix * mat4(mat3(ViewMatrix)) * vec4(aPos, 1.0);
}
