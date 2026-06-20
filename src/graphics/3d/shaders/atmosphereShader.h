#ifndef ATMOSPHERE_SHADER_H
#define ATMOSPHERE_SHADER_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

#include "compute/skyViewLUT.h"

namespace graphics {

    inline const char* atmosphereVert =
#include "screen.vert"
        ;

    inline const char* atmosphereFrag =
#include "atmosphere.frag"
        ;

    class AtmosphereShader : public ShaderProgram {
    public:
        AtmosphereShader()
            : ShaderProgram(atmosphereVert, atmosphereFrag) {
            m_invViewProjLoc = glGetUniformLocation(m_shaderProgramID, "u_InvViewProj");
            m_viewHeightLoc  = glGetUniformLocation(m_shaderProgramID, "u_ViewHeight");
            m_sunDirLoc      = glGetUniformLocation(m_shaderProgramID, "u_SunDir");
        }

        void Update(float timestep) {
            m_sunAngle += timestep * 0.00003f;
        }

        void Render(uint32_t colorBufferId, uint32_t depthBufferId, float height, const glm::mat4& invViewProj) {
            glm::vec3 sunDir = glm::normalize(glm::vec3(0.0f, glm::sin(m_sunAngle), -glm::cos(m_sunAngle)));
            m_skyView.Update(height, sunDir);

            UseShader();
            glUniformMatrix4fv(m_invViewProjLoc, 1, GL_FALSE, glm::value_ptr(invViewProj));
            glUniform1f(m_viewHeightLoc, height);
            glUniform3f(m_sunDirLoc, sunDir.x, sunDir.y, sunDir.z);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_skyView.getTransmittence().GetTransmittanceLUTId());

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_skyView.GetSkyViewLUTId());

            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, depthBufferId);

            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, colorBufferId);
        }

    private:
        SkyViewLUT m_skyView;

        float m_sunAngle = -0.3f;

        uint32_t m_invViewProjLoc;
        uint32_t m_viewHeightLoc;
        uint32_t m_sunDirLoc;
    };

}

#endif /* ATMOSPHERE_SHADER_H */
