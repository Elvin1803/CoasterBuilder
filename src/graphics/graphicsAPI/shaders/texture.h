#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics {

    enum class TextureFormat {
        RGBA8,
        RGBA16F,
        Depth24Stencil8
    };

    enum class TextureWrap {
        Repeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class TextureFilter {
        Nearest,
        Linear
    };

    struct TextureSpecification {
        uint32_t width = 0;
        uint32_t height = 0;
        TextureFormat format = TextureFormat::RGBA8;
        TextureFilter filter = TextureFilter::Linear;
        TextureWrap wrap     = TextureWrap::Repeat;
    };

    class Texture {
    public:
        Texture(const TextureSpecification& specs);
        ~Texture();

        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;

        void SetData(uint32_t slot, const char* data);
        void Bind(uint32_t slot) const;

        // Do not call resize for actual textures, it is used for frame buffers only
        void Resize(uint32_t width, uint32_t height);

        uint32_t GetId() const { return m_textureId; };

    private:
        void ApplySpecs();

    private:
        uint32_t m_textureId;

        TextureSpecification m_specs;
    };

}

#endif // TEXTURE_H
