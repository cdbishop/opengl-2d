#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D inTexture;
uniform vec3 spriteColor;

void main()
{    
    vec4 texCol = vec4(spriteColor, 1.0) * texture(inTexture, TexCoords);
    if (texCol.a < 0.1)
        discard;
    color = texCol;
}