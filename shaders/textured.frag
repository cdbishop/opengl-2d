#version 330 core

in vec3 inColour;
in vec2 TexCoord;

uniform sampler2D inTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(inTexture, TexCoord);
} 