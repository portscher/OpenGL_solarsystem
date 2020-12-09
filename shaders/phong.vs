#version 330

// Difference gouraud and phong:
// in gouraud light calculations are done per vertex
// in phong they are done per fragment

// Uniform input
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 TransformMatrix;

// Content of the vertex data (attributes)
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec2 UV;

// varying variables will be passed to the fragment shader. This values also get interpolated between vertices
out vec3 normalInt;
out vec3 vertPosInt;
out vec2 UVcoords;

void main()
{
    // Compute modelview matrix
    mat4 modelViewMatrix = ViewMatrix * TransformMatrix;
    mat4 modelViewProjectionMatrix = ProjectionMatrix * modelViewMatrix;

    // Compute a 4*4 normal matrix
    // this fixes transformations made on the model, which would make
    // the normal vector not perpendicular
    mat4 normalMatrix = transpose(inverse(modelViewMatrix));

    // Compute vertex position in Model space
    vec4 position = modelViewMatrix * vec4(Position,1.0);

    // Normal (N)
    normalInt = normalize((normalMatrix * vec4(normalize(Normal), 1.0)).xyz);

    vertPosInt = position.xyz;

    UVcoords = UV;

    gl_Position = modelViewProjectionMatrix * vec4(Position, 1.0);
}
