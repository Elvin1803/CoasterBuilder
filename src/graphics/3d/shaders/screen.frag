R""(#version 460 core

in vec2 outUVCoords;
out vec4 FragColor;

uniform sampler2D u_finalTexture;

void main()
{
    vec3 color = texture(u_finalTexture, outUVCoords).rgb;
    FragColor = vec4(color, 1.0);
}
)""