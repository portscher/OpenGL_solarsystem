#version 330

uniform float DiffuseFactor;
uniform float SpecularFactor;
uniform float AmbientFactor;
uniform mat4 ViewMatrix;
uniform int isSun;
uniform int bloomFactor;

uniform sampler2D tex;

in vec3 normalInt;
in vec3 vertPosInt;
in vec2 UVcoords; // coordinates of fragment

#define LIGHT_COUNT 3
struct Light {
    vec3 position;
    vec3 color;
};
uniform Light lights[LIGHT_COUNT];

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

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
    // Read color at UVcoords position in the texture
    vec4 TexColor = texture2D(tex, UVcoords);
    vec3 result = TexColor.rgb; // default value to current texture color

    if (isSun == 0) {
        // normalize vector again, in case its not unit anymore
        // because of interpolation
        vec3 normal = normalize(normalInt);

        vec3 lightFactor = calculatePhong(normal, vertPosInt, lights[0]);
        for(int i = 1; i < LIGHT_COUNT; i++){
            lightFactor += calculatePhong(normal, vertPosInt, lights[i]);
        }

        // Ambient Reflection: I_A = k_A * I_L
        // k_A: AmbientFactor
        // I_L: Light at Surface Location (LightColor1???)
        vec3 ambientPart = vec3(TexColor * AmbientFactor);
        vec3 result = (lightFactor + ambientPart);

        FragColor = vec4(TexColor.xyz * result, 1.);
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(result, 1.);
        BrightColor = vec4(result*bloomFactor, 1.);
    }
}
