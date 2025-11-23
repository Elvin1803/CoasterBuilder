#ifndef TEXTURE_H
#define TEXTURE_H

namespace graphics {

    class Texture {
    public:
        Texture(uint32_t width, uint32_t height, const char* data);
        ~Texture();

        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;

        void Bind(uint32_t slot) const;

    private:
        uint32_t m_textureId;

        uint32_t m_width;
        uint32_t m_height;
    };

}

#endif // TEXTURE_H
