#version 330

// Uniform input
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 TransformMatrix;

uniform float DiffuseFactor;
uniform float SpecularFactor;
uniform float AmbientFactor;
uniform int isSun;

uniform sampler2D tex;

// Content of the vertex data
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec2 UV;

#define LIGHT_COUNT 3
struct Light {
    vec3 position;
    vec3 color;
};
uniform Light lights[LIGHT_COUNT];

// Output sent to the fragment Shader
out vec4 vColor;

vec3 calculatePhong(vec3 normal, vec3 vertPos, Light light) {
    // vertex to lightsource vector (L)
    vec3 lightPos = (ViewMatrix * vec4(light.position, 1.)).xyz;
    vec3 lightDir = normalize(lightPos - vertPos);

    vec3 viewer = normalize(-vertPos.xyz);

    // half vector (H = V + L)
    vec3 halfVector1 = normalize(lightDir + viewer);

    // Diffuse reflection: I_d = k_d * I_l * n x l
    // k_d: DiffuseFactor (diffuse constant)
    // I_L: LightColor1 (Light at Surface Location)
    // n: normal
    // l: lightVector1
    // clamp(Normal x LightVector): between 0 and 1
    vec3 diffusePart = clamp(dot(normal, lightDir), 0.0, 1.0) * light.color;
    diffusePart *= vec3(DiffuseFactor);

    // Specular Reflection: I_s = k_S * I_L * (n x h)^m
    // m = shininess = 5
    // k_S: SpecularFactor
    // I_L: LightColor1 (Light at Surface Location)
    // n: normal
    // h: halfway vector
    vec3 specularPart = pow(clamp(dot(normal, halfVector1),0.0,1.0),5.0) * light.color;
    specularPart *= vec3(SpecularFactor);

    // final color is the sum of 3 terms
    // Phong Lighting Model: I = I_A + sum(I_D + I_S)
    // I_A: ambientPart (Ambient Reflection)
    // I_D: diffusePart (Diffuse Reflection)
    // I_S: specularPart (Specular Reflection)
    return diffusePart + specularPart;
}

void main()
{
    // Compute modelview matrix
    mat4 modelViewMatrix = ViewMatrix * TransformMatrix;
    mat4 modelViewProjectionMatrix = ProjectionMatrix * modelViewMatrix;

    vec4 TexColor = texture2D(tex, UV);

    if (isSun == 0) {
        // Compute a 4*4 normal matrix
        mat4 normalMatrix = transpose(inverse(modelViewMatrix));
        vec3 normal = normalize((normalMatrix * vec4(normalize(Normal), 1.0)).xyz);

        // Compute vertex position in Model space
        vec4 position = modelViewMatrix * vec4(Position,1.0);

        vec3 lightFactor = calculatePhong(normal, position.xyz, lights[0]);
        for(int i = 1; i < LIGHT_COUNT; i++){
            lightFactor += calculatePhong(normal, position.xyz, lights[i]);
        }

        // Ambient Reflection: I_A = k_A * I_L
        // k_A: AmbientFactor
        // I_L: Light at Surface Location (LightColor1???)
        vec3 ambientPart = vec3(TexColor.xyz * AmbientFactor);

        vColor = vec4(TexColor.xyz * (lightFactor + ambientPart), 1.);
    } else {
        // ignore lighting if its the sun
        vColor = vec4(TexColor.xyz, 1.);
    }


    gl_Position = modelViewProjectionMatrix * vec4(Position, 1.0);

}
