#ifndef BUFFER_H
#define BUFFER_H

#include "bufferLayout.h"
#include "graphics/graphicsAPI/shaders/texture.h"

namespace graphics {

    class Buffer {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        uint32_t m_bufferID;
    };

    class VertexBuffer : public Buffer {
    public:
        VertexBuffer(const float *vertices, uint32_t size, std::shared_ptr<BufferLayout> layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer& other) = delete;
        VertexBuffer& operator=(const VertexBuffer& other) = delete;

        virtual void Bind() const override;
        virtual void Unbind() const override;
        BufferLayout *GetLayout() const { return m_layout.get(); };

    private:
        std::shared_ptr<BufferLayout> m_layout;
    };

    class IndexBuffer : public Buffer {
    public:
        IndexBuffer(const uint32_t *indices, uint32_t count);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer& other) = delete;
        IndexBuffer& operator=(const IndexBuffer& other) = delete;

        virtual void Bind() const override;
        virtual void Unbind() const override;
        inline  uint32_t GetCount() const { return m_count; };

    private:
        uint32_t m_count;
    };

    class FrameBuffer : public Buffer {
    public:
        FrameBuffer(uint32_t width, uint32_t height);
        ~FrameBuffer();

        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer& operator=(const FrameBuffer& other) = delete;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void AddBuffer(const TextureSpecification& textureSpecs);

        void Resize(uint32_t width, uint32_t height);
        uint32_t GetColorBufferId(size_t index) const { return m_colorBuffers[index]->GetId(); }

    private:
        void RebindBuffers();

    private:
        uint32_t m_width;
        uint32_t m_height;
        std::vector<std::shared_ptr<Texture>> m_colorBuffers;
        std::shared_ptr<Texture> m_depthBuffer = nullptr;
    };

}

#endif /* BUFFER_H */
