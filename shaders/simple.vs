#version 330

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;
uniform vec3 Color;

layout (location = 0) in vec3 Position;

out vec4 vColor;

void main()
{
   gl_Position = Projection*View*Transform*vec4(Position, 1.0);
   vColor = vec4(Color, 1.);
}
