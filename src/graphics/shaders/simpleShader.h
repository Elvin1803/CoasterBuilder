#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "ShaderProgram.h"
#include "graphics/model/material.h"

namespace graphics {

    inline const char* simpleVert =
#include "simple.vert"
        ;

    inline const char* simpleFrag =
#include "simple.frag"
        ;

    class SimpleShader : public ShaderProgram {
    public:
        SimpleShader()
            : ShaderProgram(simpleVert, simpleFrag) {
            m_mvpLoc = glGetUniformLocation(m_shaderProgramID, "mvp");

            m_matKaLoc = glGetUniformLocation(m_shaderProgramID, "mat.ambiantColor");
            m_matKdLoc = glGetUniformLocation(m_shaderProgramID, "mat.diffuseColor");
            m_matKsLoc = glGetUniformLocation(m_shaderProgramID, "mat.specularColor");
            m_matNsLoc = glGetUniformLocation(m_shaderProgramID, "mat.specularExponent");
            m_matKeLoc = glGetUniformLocation(m_shaderProgramID, "mat.emissiveColor");
            m_matdLoc =  glGetUniformLocation(m_shaderProgramID, "mat.dissolve");
            m_matNiLoc = glGetUniformLocation(m_shaderProgramID, "mat.opticalDensity");

            m_hasTextureKdLoc = glGetUniformLocation(m_shaderProgramID, "mat.hasTextureKd");
            m_textureKdLoc = glGetUniformLocation(m_shaderProgramID, "u_textureKd");
        }

        const void setMVP(const glm::mat4 mvp) const {
            glUniformMatrix4fv(m_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        }

        const void setMaterial(const Material* mat) const {
            glUniform3f(m_matKaLoc, mat->ambiantColor.x, mat->ambiantColor.y, mat->ambiantColor.z);
            glUniform3f(m_matKdLoc, mat->diffuseColor.x, mat->diffuseColor.y, mat->diffuseColor.z);
            glUniform3f(m_matKsLoc, mat->specularColor.x, mat->specularColor.y, mat->specularColor.z);
            glUniform1f(m_matNsLoc, mat->specularExponent);
            glUniform3f(m_matKeLoc, mat->emissiveColor.x, mat->emissiveColor.y, mat->emissiveColor.z);
            glUniform1f(m_matdLoc, mat->dissolve);
            glUniform1f(m_matNiLoc, mat->opticalDensity);

            if (mat->textureKd != nullptr)
            {
                mat->textureKd->Bind(0);
                glUniform1i(m_textureKdLoc, 0);
                glUniform1i(m_hasTextureKdLoc, 1);
            }
            else
            {
                glUniform1i(m_hasTextureKdLoc, 0);
            }
        }

    private:
        uint32_t m_mvpLoc;

        uint32_t m_matKaLoc;
        uint32_t m_matKdLoc;
        uint32_t m_matKsLoc;
        uint32_t m_matNsLoc;
        uint32_t m_matKeLoc;
        uint32_t m_matdLoc;
        uint32_t m_matNiLoc;

        uint32_t m_hasTextureKdLoc;
        uint32_t m_textureKdLoc;
    };

}

#endif /* SIMPLE_SHADER_H */
