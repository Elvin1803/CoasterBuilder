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

out vec4 FragColor;

void main()
{
    if (mat.hasTextureKd == false)
    {
        FragColor = vec4(mat.diffuseColor.x, mat.diffuseColor.y, mat.diffuseColor.z, 1.0f);
    }
    else
    {
        FragColor = texture(u_textureKd, outUVCoords);
    }
}
)""