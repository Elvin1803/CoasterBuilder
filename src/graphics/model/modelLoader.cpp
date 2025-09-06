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
            LOG_ERROR("Could not open file {}", filename)
            return nullptr;
        }

        std::shared_ptr<Model> model = std::make_shared<Model>();

        // Reading file
        while (file.peek() != EOF) {
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

            uint32_t vertexAttribsLength;
            file.read(reinterpret_cast<char*>(&vertexAttribsLength), sizeof(vertexAttribsLength));
            std::vector<float> vertices(vertexAttribsLength / sizeof(float));
            file.read(reinterpret_cast<char*>(vertices.data()), vertexAttribsLength);

#ifdef DEBUG
            for (size_t i = 0; i < vertices.size(); i += 8) {
              LOG_TRACE(
                  "vertex {}: position: {}, {}, {} | normals {}, {}, {} | \
textureCoordinates {}, {}",
                          i / 8,
                          vertices[i + 0], vertices[i + 1], vertices[i + 2],
                          vertices[i + 3], vertices[i + 4], vertices[i + 5],
                          vertices[i + 6], vertices[i + 7]);
            }
#endif /* DEBUG */

            uint32_t indicesLength;
            file.read(reinterpret_cast<char*>(&indicesLength), sizeof(indicesLength));
            std::vector<uint32_t> indices(indicesLength / sizeof(uint32_t));
            file.read(reinterpret_cast<char*>(indices.data()), indicesLength);

#ifdef DEBUG
            for (size_t i = 0; i < indices.size(); i += 3) {
                LOG_TRACE("face {}: {}, {}, {}",
                          i / 3,
                          indices[i + 0], indices[i + 1], indices[i + 2]);
            }
#endif /* DEBUG */

            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

            std::unique_ptr<VertexBuffer> vbo =
                std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float), layout);
            std::unique_ptr<IndexBuffer> ibo =
                std::make_unique<IndexBuffer>(indices.data(), indices.size() * sizeof(uint32_t));
            const std::shared_ptr<VertexArray> vao =
                std::make_shared<VertexArray>(std::move(vbo), std::move(ibo));

            mesh->AddSubMesh(vao);
            ModelNode node;
            node.mesh = mesh;

            model->AddNode(name, parentName, node);

            // FIXME: calculate origin etc
            // FIXME: handle parenting
        }

        // FIXME
        return model;
    }

}
