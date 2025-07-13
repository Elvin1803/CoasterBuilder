#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include <pch.h>
#include "ShaderProgram.h"

namespace renderer {

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
        }

        const void setMVP(const glm::mat4 mvp) const {
            glUniformMatrix4fv(m_mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        }

    private:
        uint32_t m_mvpLoc;
    };

}

#endif /* SIMPLE_SHADER_H */
