#include <pch.h>
#include "texture.h"

namespace graphics {

    Texture::Texture(uint32_t width, uint32_t height, const char* data)
        : m_width(width), m_height(height) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);

        glTextureStorage2D(m_textureId, 1, GL_RGBA8, m_width, m_height);
        glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &m_textureId);
    }

    void Texture::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_textureId);
    }

}
