R""(#version 330 core

in vec3 outNorm;
in vec2 outUVCoords;

struct Material
{
    vec3 ambiantColor;      // Ka
    vec3 diffuseColor;      // Kd
    vec3 specularColor;     // Ks
    float specularExponent; // Ns
    vec3 emissiveColor;     // Ke
    float dissolve;         // d
    float opticalDensity;   // Ni

    bool hasTextureKd;
};
uniform Material mat;

uniform sampler2D u_textureKd;
uniform bool u_current;

out vec4 FragColor;

void main()
{
    vec4 baseColor;
    if (mat.hasTextureKd == false)
    {
        baseColor = vec4(mat.diffuseColor.x, mat.diffuseColor.y, mat.diffuseColor.z, 1.0f);
    }
    else
    {
        baseColor = texture(u_textureKd, outUVCoords);
    }

    if (u_current)
    {
        // 67 67 67 67 67 67 67
        baseColor.rgb = mix(baseColor.rgb, vec3(0.2, 0.2, 1.0), 0.67);
        baseColor.a = 0.4f;
    }

    FragColor = baseColor;
}
)""