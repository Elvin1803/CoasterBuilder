#include <pch.h>
#include "buffer.h"

namespace graphics {

    VertexBuffer::VertexBuffer(const float *vertices, uint32_t size, std::shared_ptr<BufferLayout> layout)
        : m_layout(layout) {
        glCreateBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_bufferID);
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBuffer::IndexBuffer(const uint32_t *indices, uint32_t count)
        : m_count(count) {
        glCreateBuffers(1, &m_bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_bufferID);
    }

    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    }

    void IndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
        : m_width(width), m_height(height) {
        glCreateFramebuffers(1, &m_bufferID);
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &m_bufferID);
    }

    void FrameBuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
    }

    void FrameBuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::AddBuffer(const TextureSpecification& textureSpecs) {
        if (textureSpecs.format == TextureFormat::Depth24Stencil8) {
            m_depthBuffer = std::make_shared<Texture>(textureSpecs);
        } else {
            m_colorBuffers.emplace_back(std::make_shared<Texture>(textureSpecs));
        }

        RebindBuffers();
    }

    void FrameBuffer::Resize(uint32_t width, uint32_t height) {
        m_width = width;
        m_height = height;

        for (auto& buffer : m_colorBuffers) {
            buffer->Resize(width, height);
        }

        m_depthBuffer->Resize(width, height);

        RebindBuffers();
    }

    void FrameBuffer::RebindBuffers() {
        std::vector<GLenum> drawBuffers;

        for (size_t i = 0; i < m_colorBuffers.size(); i++) {
            GLenum attachmentSlot = GL_COLOR_ATTACHMENT0 + i;
            glNamedFramebufferTexture(m_bufferID, attachmentSlot, GetColorBufferId(i), 0);
            drawBuffers.push_back(attachmentSlot);
        }

        if (!drawBuffers.empty()) {
            glNamedFramebufferDrawBuffers(m_bufferID, static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
        } else {
            glNamedFramebufferDrawBuffers(m_bufferID, 0, nullptr);
        }

        if (m_depthBuffer) {
            glNamedFramebufferTexture(m_bufferID, GL_DEPTH_STENCIL_ATTACHMENT, m_depthBuffer->GetId(), 0);
        }
    }

}
