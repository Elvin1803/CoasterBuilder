#include <pch.h>
#include "texture.h"
#include "glad/glad.h"

namespace graphics {

    static GLenum GetGLFormat(TextureFormat format) {
        switch (format) {
        case TextureFormat::RGBA16F:
        {
            return GL_RGBA16F;
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

    static GLenum GetGLWrap(TextureWrap wrap) {
        switch (wrap) {
        case TextureWrap::ClampToEdge:
        {
            return GL_CLAMP_TO_EDGE;
        }
        case TextureWrap::ClampToBorder:
        {
            return GL_CLAMP_TO_BORDER;
        }
        default:
        {
            return GL_REPEAT;
        }
        }
    }

    Texture::Texture(const TextureSpecification& specs)
        : m_specs(specs) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);

        ApplySpecs();
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

    void Texture::Resize(uint32_t width, uint32_t height) {
        if (m_specs.width == width && m_specs.height == height) return;

        m_specs.width = width;
        m_specs.height = height;

        glDeleteTextures(1, &m_textureId);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);

        ApplySpecs();
    }

    void Texture::ApplySpecs() {
        glTextureStorage2D(m_textureId, 1, GetGLFormat(m_specs.format), m_specs.width, m_specs.height);
        // Filter
        GLenum glFilter = (m_specs.filter == TextureFilter::Linear) ? GL_LINEAR : GL_NEAREST;
        glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, glFilter);
        glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, glFilter);
        // Wrap
        glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_S, GetGLWrap(m_specs.wrap));
    }

}
