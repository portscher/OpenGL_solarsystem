#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec2 UV;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 TransformMatrix;

out Data
{
    vec4 position;
    vec4 normal;
    vec4 color;
    mat4 mvp;
} vdata;

void main()
{
    mat4 mv = ViewMatrix*TransformMatrix;
    vdata.mvp = ProjectionMatrix * mv;
    vdata.position = vec4(Position, 1.);
    vdata.normal = vec4(Normal, 1.);
}
