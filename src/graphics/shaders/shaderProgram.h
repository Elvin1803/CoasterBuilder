#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

namespace graphics {

    class ShaderProgram {
    public:
        ShaderProgram(const char* vertexCode, const char* fragmentCode);
        virtual ~ShaderProgram();

        inline uint32_t GetID() const { return m_shaderProgramID; };

        void UseShader() const;

    protected:
        uint32_t m_shaderProgramID;
    };

}

#endif /* SHADER_PROGRAM_H */
