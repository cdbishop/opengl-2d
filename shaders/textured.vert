#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColour;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    //gl_Position = projection * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	outColour = aColor;
	TexCoord = aTexCoord;
}