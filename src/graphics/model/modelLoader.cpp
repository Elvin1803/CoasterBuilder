#include <pch.h>
#include "modelLoader.h"

#include "graphics/buffers/buffer.h"

#include "utils/logger.h"

namespace graphics::modelLoader {

    std::shared_ptr<graphics::BufferLayout> layout = std::make_shared<graphics::BufferLayout>(
        std::vector<graphics::BufferLayoutElement>{
            { 3, graphics::ShaderDataType::Float }, // Position
            { 3, graphics::ShaderDataType::Float }, // Normals
            { 2, graphics::ShaderDataType::Float }, // Texture coordinates
        });

    std::shared_ptr<graphics::Model> LoadModel(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            LOG_ERROR("Could not open file {}", filename);
            return nullptr;
        }

        std::shared_ptr<Model> model = std::make_shared<Model>();
        std::unordered_map<std::string, std::shared_ptr<Material>> materials;

        // Parse materials:
        uint32_t numberOfMaterials;
        file.read(reinterpret_cast<char*>(&numberOfMaterials), sizeof(numberOfMaterials));
#ifdef DEBUG
        LOG_TRACE("Number of materials: {}", numberOfMaterials);
#endif /* DEBUG */

        for (uint32_t i = 0; i < numberOfMaterials; i++) {
            std::shared_ptr<Material> material = std::make_shared<Material>();

            // Read name of the material
            uint32_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            std::string name(nameLength, '\0');
            file.read(&name[0], nameLength);

#ifdef DEBUG
            LOG_TRACE("Material name: {}", name);
#endif /* DEBUG */

            glm::vec3 ambiantColor;
            file.read(reinterpret_cast<char*>(&ambiantColor), sizeof(glm::vec3));
            material->ambiantColor = ambiantColor;

            glm::vec3 diffuseColor;
            file.read(reinterpret_cast<char*>(&diffuseColor), sizeof(glm::vec3));
            material->diffuseColor = diffuseColor;

            glm::vec3 specularColor;
            file.read(reinterpret_cast<char*>(&specularColor), sizeof(glm::vec3));
            material->specularColor = specularColor;

            float specularExponent;
            file.read(reinterpret_cast<char*>(&specularExponent), sizeof(specularExponent));
            material->specularExponent = specularExponent;

            glm::vec3 emissiveColor;
            file.read(reinterpret_cast<char*>(&emissiveColor), sizeof(glm::vec3));
            material->emissiveColor = emissiveColor;

            float dissolve;
            file.read(reinterpret_cast<char*>(&dissolve), sizeof(dissolve));
            material->dissolve = dissolve;

            float opticalDensity;
            file.read(reinterpret_cast<char*>(&opticalDensity), sizeof(opticalDensity));
            material->opticalDensity = opticalDensity;

            uint32_t KdWidth;
            file.read(reinterpret_cast<char*>(&KdWidth), sizeof(KdWidth));
            if (KdWidth != 0) {
                uint32_t KdHeight;
                file.read(reinterpret_cast<char*>(&KdHeight), sizeof(KdHeight));

                std::vector<char> textureKd(KdWidth * KdHeight * 4);
                file.read(reinterpret_cast<char*>(textureKd.data()), KdWidth * KdHeight * 4);

                material->textureKd = std::make_unique<Texture>(KdWidth, KdHeight, textureKd.data());
            }

            materials.emplace(name, material);
        }

        // Parse meshes
        uint32_t numberOfMeshes;
        file.read(reinterpret_cast<char*>(&numberOfMeshes), sizeof(numberOfMeshes));
#ifdef DEBUG
        LOG_TRACE("Number of meshes: {}", numberOfMeshes);
#endif /* DEBUG */

        for (uint32_t i = 0; i < numberOfMeshes; i++) {
            // Read name of the mesh
            uint32_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            std::string name(nameLength, '\0');
            file.read(&name[0], nameLength);

#ifdef DEBUG
            LOG_TRACE("Mesh name: {}", name);
#endif /* DEBUG */

            // Check if the mesh has a parent
            uint32_t parentNameLength;
            file.read(reinterpret_cast<char*>(&parentNameLength), sizeof(parentNameLength));
            std::string parentName(parentNameLength, '\0');
            file.read(&parentName[0], parentNameLength);

#ifdef DEBUG
            LOG_TRACE("Parent Mesh name: {}", parentName);
#endif /* DEBUG */

            glm::vec3 origin;
            file.read(reinterpret_cast<char*>(&origin), sizeof(glm::vec3));

            // Check if the mesh has a material
            uint32_t materialNameLength;
            file.read(reinterpret_cast<char*>(&materialNameLength), sizeof(materialNameLength));
            std::string materialName(materialNameLength, '\0');
            file.read(&materialName[0], materialNameLength);

#ifdef DEBUG
            LOG_TRACE("Mesh material name: {}", materialName);
#endif // DEBUG

            uint32_t vertexAttribsLength;
            file.read(reinterpret_cast<char*>(&vertexAttribsLength), sizeof(vertexAttribsLength));
            std::vector<float> vertices(vertexAttribsLength / sizeof(float));
            file.read(reinterpret_cast<char*>(vertices.data()), vertexAttribsLength);

            uint32_t indicesLength;
            file.read(reinterpret_cast<char*>(&indicesLength), sizeof(indicesLength));
            std::vector<uint32_t> indices(indicesLength / sizeof(uint32_t));
            file.read(reinterpret_cast<char*>(indices.data()), indicesLength);

            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

            std::unique_ptr<VertexBuffer> vbo =
                std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float), layout);
            std::unique_ptr<IndexBuffer> ibo =
                std::make_unique<IndexBuffer>(indices.data(), indices.size() * sizeof(uint32_t));
            const std::shared_ptr<VertexArray> vao =
                std::make_shared<VertexArray>(std::move(vbo), std::move(ibo));

            if (materialNameLength == 0) {
                mesh->AddSubMesh(vao);
            } else {
                mesh->AddSubMesh(vao, materials[materialName]);
            }
            ModelNode node;
            node.mesh = mesh;
            node.origin = origin;

            model->AddNode(name, parentName, node);
        }

        return model;
    }

}
