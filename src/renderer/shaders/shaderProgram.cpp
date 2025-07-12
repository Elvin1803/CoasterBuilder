#include <pch.h>
#include "ShaderProgram.h"

#include "utils/logger.h"

namespace renderer
{

    ShaderProgram::ShaderProgram(const char* vertexCode, const char* fragmentCode)
    {
        // Vertex shader
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexCode, nullptr);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG_ERROR("Could not compile vertex shader: {}", infoLog);
        }

        // Fragment shader
        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG_ERROR("Could not compile fragment shader: {}", infoLog);
        }

        // Create shader program
        m_shaderProgramID = glCreateProgram();
        glAttachShader(m_shaderProgramID, vertexShader);
        glAttachShader(m_shaderProgramID, fragmentShader);
        glLinkProgram(m_shaderProgramID);

        // Clean up
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_shaderProgramID);
    }

    void ShaderProgram::UseShader() const
    {
        glUseProgram(m_shaderProgramID);
    }

}
