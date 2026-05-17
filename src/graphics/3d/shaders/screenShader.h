#ifndef SCREEN_SHADER_H
#define SCREEN_SHADER_H

#include "graphics/graphicsAPI/shaders/shaderProgram.h"

namespace graphics {

    inline const char* screenVert =
#include "screen.vert"
        ;

    inline const char* screenFrag =
#include "screen.frag"
        ;

    class ScreenShader : public ShaderProgram {
    public:
        ScreenShader()
            : ShaderProgram(screenVert, screenFrag) {
            UseShader();
            glUniform1i(glGetUniformLocation(m_shaderProgramID, "u_finalRender"), 0);
        }
    };

}

#endif /* SCREEN_SHADER_H */
