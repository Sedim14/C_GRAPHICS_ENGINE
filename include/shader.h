#ifndef SHADER_H
#define SHADER_H

#include<stdlib.h>
#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<stdbool.h>

//Linked list represents all the shaders that will compose the shader program
typedef struct shader
{
	unsigned int ID;
	GLenum shaderType;
	struct shader *next; 
}TSHADER;

char *loadSource(char *path);
TSHADER *createShaderNode(GLenum type,char *sourcePath); //Shader node that will execute those 3 functions aboe, and if it executes them complie will return the new shader source
void addShader(TSHADER *sh,GLenum type,char *sourcePath); //Add new shader to a shader list

#endif
