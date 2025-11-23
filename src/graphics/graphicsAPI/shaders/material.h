#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"

namespace graphics
{

    struct Material {
    public:
        glm::vec3 ambiantColor  = glm::vec3(0); // Ka
        glm::vec3 diffuseColor  = glm::vec3(0); // Kd
        glm::vec3 specularColor = glm::vec3(0); // Ks
        float specularExponent  = 0;            // Ns
        glm::vec3 emissiveColor = glm::vec3(0); // Ke
        float dissolve          = 0;            // d
        float opticalDensity    = 0;            // Ni

        std::unique_ptr<Texture> textureKd = nullptr;
    };

}

#endif // MATERIAL_H
