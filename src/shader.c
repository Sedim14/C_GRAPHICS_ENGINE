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
	if(!glslCode)//Check if source code has been loaded correctly
	{
		printf("ERROR::COULD NOT CREATE SHADER!\n");
		return NULL;
	}
	int success;
	char infoLog[512];
	//Create  and aattach shader
	new->ID = glCreateShader(type);
	glShaderSource(new->ID,1,&glslCode,NULL);
	//Compile Shader
	glCompileShader(new->ID);
	glGetShaderiv(new->ID,GL_COMPILE_STATUS,&success);
	if(!success) //CHeck if it compile correctly
	{
		glGetShaderInfoLog(new->ID,512,NULL,infoLog);
		printf("ERROR!!SHADER_COMPILATION_FAILED: %s\n",infoLog);
		return NULL;
	}
	new->next = NULL;
	printf("%s compiled succesfully\n",sourcePath);

	return new;
}

void addShader(TSHADER **sh,GLenum type,char *sourcePath)
{
	TSHADER *new = createShaderNode(type,sourcePath);

	if(!new)
		exit(0);

	if(!*sh)
	{
		*sh = new;
	}
	else
	{
		TSHADER *shader = *sh;
		while(shader->next)
			shader = shader->next;
		shader->next=new;

	}
}

void deleteShaders(TSHADER **sh)
{
	TSHADER *current = *sh;
	TSHADER *next;
	while(current)
	{
		next = current->next;
		glDeleteShader(current->ID);
		free(current);
	        current = next;	
	}
	*sh = NULL;

}

//Only call this function assuming all shaders compiled succesfuly
SHADERPROGRAM createShaderProgram(TSHADER** shaders)
{
	int success;
	char infoLog[512];
	SHADERPROGRAM shaderProgram;//Reference of te program
	shaderProgram = glCreateProgram();
	TSHADER *sh = *shaders;

	if(!sh)
	{
		printf("Error:: No shaders exist to attach to the program!!\n");
		exit(-1);
	}

	while(sh)
	{
		glAttachShader(shaderProgram,sh->ID);
		sh = sh->next;
	}
	printf("Shaders Attached Succesfully\n");
	//Link those shaders that have been attached to thew shader program
	glLinkProgram(shaderProgram);
	//Ceck if the program was created succesfully
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
		printf("ERROR:: %s\n",infoLog);
		exit(-1);
	}
	//DeleteShaders since we don't need them anymore because they have been linked to the program
	printf("Shader Program has been created succesfully!!!\n");
	deleteShaders(&sh);
	return shaderProgram;
}

void deleteShaderProgram(SHADERPROGRAM *program)
{
	glDeleteProgram(*program);
}

void printShaders(TSHADER *head) {
    while (head) {
        printf("Shader ID: %u\n", head->ID);
        head = head->next;
    }
}
