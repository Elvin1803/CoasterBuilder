R""(#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUVCoords;

uniform mat4 mvp;

out vec3 outNorm;
out vec2 outUVCoords;

void main()
{
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    outNorm = aNorm;
    outUVCoords = aUVCoords;
}
)""