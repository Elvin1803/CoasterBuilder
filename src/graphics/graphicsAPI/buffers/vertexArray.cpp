#include <pch.h>
#include "vertexArray.h"

#include "utils/logger.h"

namespace graphics {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Int:   return GL_INT;
        case ShaderDataType::Bool:  return GL_BOOL;
        default:                    return 0;
        }
    }

    VertexArray::VertexArray(std::unique_ptr<VertexBuffer> vbo, std::unique_ptr<IndexBuffer> ibo) {
        glCreateVertexArrays(1, &m_vaoID);
        glBindVertexArray(m_vaoID);

        // Set vertex buffer
        vbo->Bind();
        uint32_t attribIndex = 0;
        auto *layout = vbo->GetLayout();
        for (const auto& element : layout->GetLayout()) {
            switch (element.type) {
            case ShaderDataType::Float:
            {
                glVertexAttribPointer(attribIndex, element.count,
                                      ShaderDataTypeToOpenGLBaseType(element.type),
                                      element.normalized ? GL_TRUE : GL_FALSE,
                                      layout->GetStride(),
                                      reinterpret_cast<const void*>(element.offset));
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::Bool:
            {
                glVertexAttribIPointer(attribIndex, element.count,
                                       ShaderDataTypeToOpenGLBaseType(element.type),
                                       layout->GetStride(),
                                       reinterpret_cast<const void*>(element.offset));
                break;
            }
            default:
            {
                LOG_WARN("Did not recognize the shader data type");
                return;
            }
            }

            glEnableVertexAttribArray(attribIndex);
            attribIndex++;
        }

        m_vbo = std::move(vbo);

        // set index buffer
        m_ibo = std::move(ibo);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_vaoID);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_vaoID);
        m_ibo->Bind();
    }

}
