#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics {

    enum class TextureFormat {
        RGBA8,
        RGB16F,
        Depth24Stencil8
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
    };

    class Texture {
    public:
        Texture(const TextureSpecification& specs);
        ~Texture();

        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;

        void SetData(uint32_t slot, const char* data);
        void Bind(uint32_t slot) const;

    private:
        uint32_t m_textureId;

        TextureSpecification m_specs;
    };

}

#endif // TEXTURE_H
