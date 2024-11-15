#ifndef SHADER_H
#define SHADER_H

#include<stdlib.h>
#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<stdbool.h>
#include"Vector.h"

//Linked list represents all the shaders that will compose the shader program
typedef struct shader
{
	unsigned int ID;
	struct shader *next; 
}TSHADER;

//Structure that will represent the shader program
typedef unsigned int SHADERPROGRAM;

//Functions for loading and compiling shaders source codes
char *loadSource(char *path);
TSHADER *createShaderNode(GLenum type,char *sourcePath); //Shader node that will execute those 3 functions aboe, and if it executes them complie will return the new shader source
void addShader(TSHADER **sh,GLenum type,char *sourcePath); //Add new shader to a shader list
void deleteShaders(TSHADER **sh); //Delete all shaders used for the program once they have bee linked
void printShaders(TSHADER *head);

//Functions for creating and manipulating a shader program
SHADERPROGRAM createShaderProgram(TSHADER** shaders);//Attaches all shaders and links them
void deleteShaderProgram(SHADERPROGRAM *program);
void useShader(SHADERPROGRAM *program);

//Manipulating our uniforms variable for shaders programs
void setVector4f(SHADERPROGRAM *program,FVECTOR4D *vector,const char *uniform);
void setVector4i(SHADERPROGRAM *program,IVECTOR4D *vector,const char *uniform);
void setFloat(SHADERPROGRAM *program,float value,const char *uniform);
void setInt(SHADERPROGRAM *program,int value,const char *uniform);
void setBool(SHADERPROGRAM *program,bool value,const char *uniform);
#endif
