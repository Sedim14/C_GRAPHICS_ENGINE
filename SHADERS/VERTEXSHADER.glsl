#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inputColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 aColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
	aColor = vec4(inputColor.x,inputColor.y,inputColor.z,1.0);
	TexCoord = aTexCoord;
}
