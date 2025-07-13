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
        : ShaderProgram(simpleVert, simpleFrag) {}

    };

}

#endif /* COLOR_SHADER_H */
