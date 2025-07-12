#ifndef BUFFER_H
#define BUFFER_H

#include "bufferLayout.h"

namespace renderer {

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

        virtual void Bind() const;
        virtual void Unbind() const;
        BufferLayout *GetLayout() const { return m_layout.get(); };

    private:
        std::shared_ptr<BufferLayout> m_layout;
    };

    class IndexBuffer : public Buffer {
    public:
        IndexBuffer(const uint32_t *indices, uint32_t count);
        ~IndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;
        inline  uint32_t GetCount() const { return m_count; };

    private:
        uint32_t m_count;
    };

}

#endif /* BUFFER_H */
