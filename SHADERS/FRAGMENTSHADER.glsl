#version 330 core
out vec4 FragColor;

uniform vec4 modifiedColor;

void main()
{
	FragColor = modifiedColor;
}
