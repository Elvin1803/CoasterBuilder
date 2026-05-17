#ifndef SKY_VIEW_LUT_H
#define SKY_VIEW_LUT_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

#include "transmittanceLUT.h"
#include "multiScatLUT.h"

namespace graphics {

    inline const char* skyViewCompute =
#include "skyView.comp"
        ;

    class SkyViewLUT : public ShaderProgram {
    public:
        SkyViewLUT()
            : ShaderProgram(skyViewCompute) {
            m_skyViewLUT = std::make_unique<Texture>(
                TextureSpecification{200, 200, TextureFormat::RGBA16F,
                                     TextureFilter::Linear, TextureWrap::ClampToEdge}
                );
        }

        void Update(float viewHeight, const glm::vec3& sunDir) {
            UseShader();

            glUniform1f(glGetUniformLocation(m_shaderProgramID, "u_ViewHeight"), viewHeight);
            glUniform3fv(glGetUniformLocation(m_shaderProgramID, "u_SunDir"), 1, &sunDir.x);

            uint32_t nativeTexId = m_skyViewLUT->GetId();
            glBindImageTexture(0, nativeTexId, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_transmittance.GetTransmittanceLUTId());
            glUniform1i(glGetUniformLocation(m_shaderProgramID, "u_TransmittanceLUT"), 1);

            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, m_multiScat.GetMultiScatLUTId());
            glUniform1i(glGetUniformLocation(m_shaderProgramID, "u_MultiScatteringLUT"), 2);

            glDispatchCompute(200 / 8, 200 / 8, 1);
            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        }

        uint32_t GetSkyViewLUTId() const { return m_skyViewLUT->GetId(); }

        const TransmittanceLUT& getTransmittence() { return m_transmittance; };
        const MultiScatLUT& GetMultiScat() { return m_multiScat; };

    private:
        TransmittanceLUT m_transmittance;
        MultiScatLUT m_multiScat;
        std::unique_ptr<Texture> m_skyViewLUT;
    };

}

#endif /* SKY_VIEW_LUT_H */
