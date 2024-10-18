#include"shader.h"

char *loadSource(char *path)
{
	FILE *file = fopen(path,"r");
	if(!file)
	{
		printf("Failed to open GLSL file: %s\n",path);
		return NULL;
	}
	//Get the size of the glsl
	fseek(file,0,SEEK_END);//move to end of file
	long fileSize = ftell(file); //Get the size at current file pos
	rewind(file); //Move to start of file to read the file form start
	
	char *shaderCode = (char*)malloc(fileSize+1);
	if(!shaderCode)
	{
		printf("Memory allocation failed\n");
		fclose(file);
		return NULL;
	}

	//read the file
	fread(shaderCode,1,fileSize,file);
	shaderCode[fileSize] = '\0';

	fclose(file);

	return shaderCode;
}

TSHADER *createShaderNode(GLenum type,char *sourcePath)
{
	TSHADER *new = (TSHADER*)malloc(sizeof(TSHADER));
	if(!new)
	{
		printf("ERROR::COULD NOT CREATE SHADER!\n");
		return NULL;
	}
	//Load shader source
	const char *glslCode = loadSource(sourcePath);
	if(!glslCode)
	{
		printf("ERROR::COULD NOT CREATE SHADER!\n");
		return NULL;
	}
	int success;
	char infoLog[512];
	//Create  and aattach shader9
	new->ID = glCreateShader(type);
	glShaderSource(new->ID,1,&glslCode,NULL);
	//Compile Shader
	glCompileShader(new->ID);
	glGetShaderiv(new->ID,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(new->ID,512,NULL,infoLog);
		printf("ERROR!!SHADER_COMPILATION_FAILED\n");
		return NULL;
	}

	return new;
}

void addShader(TSHADER *sh,GLenum type,char *sourcePath)
{
	if(sh==NULL)
	{
		sh = createShaderNode(type,sourcePath);
	}
	else
	{
		addShader(sh->next,type,sourcePath);
	}
}
