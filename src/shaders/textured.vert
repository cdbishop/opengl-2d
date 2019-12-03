#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform float repeatFactorU;
uniform float repeatFactorV;

void main()
{
    //TexCoords = vertex.zw;    
    TexCoords = vec2(vertex.z * repeatFactorU, vertex.w * repeatFactorV);
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}