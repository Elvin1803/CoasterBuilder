#include <pch.h>
#include "texture.h"

namespace graphics {

    static GLenum GetGLFormat(TextureFormat format) {
        switch (format) {
        case TextureFormat::RGB16F:
        {
            return GL_RGB16F;
        }
        case TextureFormat::Depth24Stencil8:
        {
            return GL_DEPTH24_STENCIL8;
        }
        default:
        {
            return GL_RGBA8;
        }
        }
    }

    Texture::Texture(const TextureSpecification& specs)
        : m_specs(specs) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);

        glTextureStorage2D(m_textureId, 1, GetGLFormat(specs.format), specs.width, specs.height);
        GLenum glFilter = (specs.filter == TextureFilter::Linear) ? GL_LINEAR : GL_NEAREST;
        glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, glFilter);
        glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, glFilter);
    }

    void Texture::SetData(uint32_t slot, const char* data) {
        Bind(slot);
        glTextureSubImage2D(m_textureId, 0, 0, 0, m_specs.width, m_specs.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }


    Texture::~Texture() {
        glDeleteTextures(1, &m_textureId);
    }

    void Texture::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_textureId);
    }

}
