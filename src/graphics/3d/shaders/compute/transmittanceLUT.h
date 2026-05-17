#ifndef TRANSMITTANCE_LUT_H
#define TRANSMITTANCE_LUT_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

#include "graphics/graphicsAPI/shaders/texture.h"

namespace graphics {

    inline const char* transmittanceCompute =
#include "transmittance.comp"
        ;

    class TransmittanceLUT : public ShaderProgram {
    public:
        TransmittanceLUT()
            : ShaderProgram(transmittanceCompute) {
            m_transmittanceLUT = std::make_unique<Texture>(
                TextureSpecification{256, 64, TextureFormat::RGBA16F,
                                     TextureFilter::Nearest, TextureWrap::ClampToEdge}
                );

            UseShader();

            uint32_t nativeTexId = m_transmittanceLUT->GetId();
            glBindImageTexture(0, nativeTexId, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
            glDispatchCompute(256 / 8, 64 / 8, 1);
            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        }

        uint32_t GetTransmittanceLUTId() const { return m_transmittanceLUT->GetId(); }

    private:
        std::unique_ptr<Texture> m_transmittanceLUT;
    };

}

#endif /* TRANSMITTANCE_LUT_H */
