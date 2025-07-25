#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "buffer.h"

namespace renderer {

    class VertexArray {
    public:
        VertexArray(std::unique_ptr<VertexBuffer> vbo, std::unique_ptr<IndexBuffer> ibo);
        ~VertexArray();

        void Bind() const;

    private:
        uint32_t m_vaoID;

        std::unique_ptr<VertexBuffer> m_vbo = nullptr;
        std::unique_ptr<IndexBuffer> m_ibo = nullptr;
    };

}

#endif /* VERTEX_ARRAY_H */
