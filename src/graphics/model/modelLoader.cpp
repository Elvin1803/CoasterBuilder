#include <memory>
#include <pch.h>
#include "modelLoader.h"

#include "utils/logger.h"

namespace graphics::modelLoader {

    std::shared_ptr<graphics::Model> LoadModel(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            LOG_ERROR("Could not open file {}", filename)
            return nullptr;
        }

        while (file.peek() != EOF) {
            // Read name of the mesh
            uint32_t nameLength;
            file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            std::string name(nameLength, '\0');
            file.read(&name[0], nameLength);

#ifdef DEBUG
            LOG_TRACE("Mesh name: {}", name);
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
        }

        return nullptr;
    }

}
