#version 330

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 TransformMatrix;

layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec2 UV;

out vec2 UVcoords;

void main()
{
// summing up matrices
   gl_Position = ProjectionMatrix*ViewMatrix*TransformMatrix*vec4(Position.x, Position.y, Position.z, 1.0);

   UVcoords = UV;
}
