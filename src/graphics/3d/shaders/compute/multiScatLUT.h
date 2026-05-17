#ifndef MULTI_SCAT_LUT_H
#define MULTI_SCAT_LUT_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

#include "graphics/graphicsAPI/shaders/texture.h"
#include "transmittanceLUT.h"

namespace graphics {

    inline const char* multiScatCompute =
#include "multiScat.comp"
        ;

    class MultiScatLUT : public ShaderProgram {
    public:
        MultiScatLUT()
            : ShaderProgram(multiScatCompute) {
            m_multiScatLUT = std::make_unique<Texture>(
                TextureSpecification{32, 32, TextureFormat::RGBA16F,
                                     TextureFilter::Linear, TextureWrap::ClampToEdge}
                );

            UseShader();

            uint32_t nativeTexId = m_multiScatLUT->GetId();
            glBindImageTexture(0, nativeTexId, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_transmittance.GetTransmittanceLUTId());
            glUniform1i(glGetUniformLocation(m_shaderProgramID, "u_TransmittanceLUT"), 1);
            glDispatchCompute(32 / 8, 32 / 8, 1);
            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        }

        uint32_t GetMultiScatLUTId() const { return m_multiScatLUT->GetId(); }

    private:
        TransmittanceLUT m_transmittance;
        std::unique_ptr<Texture> m_multiScatLUT;
    };

}

#endif /* MULTI_SCAT_LUT_H */
