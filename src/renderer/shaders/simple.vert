R""(#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 mvp;

out vec4 outCol;

void main()
{
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    outCol = vec4(aCol.x, aCol.y, aCol.z, 1.0);
}
)""