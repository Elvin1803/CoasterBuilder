#ifndef ATMOSPHERE_SHADER_H
#define ATMOSPHERE_SHADER_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

// FIXME
namespace graphics {

    inline const char* screenVert =
#include "screen.vert"
        ;

    inline const char* screenFrag =
#include "screen.frag"
        ;

    class AtmosphereShader : public ShaderProgram {
    public:
        AtmosphereShader()
            : ShaderProgram(screenVert, screenFrag) {
            UseShader();
            glUniform1i(glGetUniformLocation(m_shaderProgramID, "u_finalRender"), 0);
        }
    };

}

#endif /* ATMOSPHERE_SHADER_H */
