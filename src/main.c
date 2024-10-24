#include<glad/glad.h>
#include<stdlib.h>
#include<GLFW/glfw3.h>
#include<stdbool.h>
#include"window.h"
#include"shader.h"
#include<math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Window mainWindow =
{
	NULL,
	"Window",
	600,
	600
};

void frame_buffer_size_callback(GLFWwindow* w,int width,int height);

//Shader Paths
char* vertexShaderSource = "./SHADERS/VERTEXSHADER.glsl";
char* fragmentShaderSource = "./SHADERS/FRAGMENTSHADER.glsl";

TSHADER *myShaders = NULL;
SHADERPROGRAM shaderProgram;

float vertices[] = {
	// positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned int indices[] ={
	0, 1, 3,   // first triangle
    	1, 2, 3    // second triangle
};

int main(int argv,char* argc[])
{	//This is commentary added to tost git
	glfwInit();
	setWindowVersion(3);

	if(!startWindow(&mainWindow))
		exit(-1);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
       	{
          	printf("Failed to initialize GLAD\n");
	 	 exit(-1);
      	}

	
	//Compile, Attach, and Create Shader Programs
	addShader(&myShaders,GL_VERTEX_SHADER,vertexShaderSource);
	addShader(&myShaders,GL_FRAGMENT_SHADER,fragmentShaderSource);
	printShaders(myShaders);
	shaderProgram = createShaderProgram(&myShaders);


	
	//lOAD VBOS AND VAOS, and textures
	unsigned int VBO, VAO, EBO, texture;
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&EBO);
	glGenTextures(1,&texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D,texture);
	//Setting texture wrapping and filtering options
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("./TEXTURES/container.jpg",&width,&height,&nrChannels,0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("ERROR::Failed to load texture\n!!");
		exit(-1);
	}

	stbi_image_free(data);


	//Enabling attributes of the model
	//Enabling position attribiute
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//Enabling Color Attribute
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//Enabling Texture Attribute
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	glfwSetFramebufferSizeCallback(mainWindow.window,frame_buffer_size_callback);
	glViewport(0,0,mainWindow.width,mainWindow.height);//Set and start the rendering window for the current window that has been created
							   

	while(windowIsOpen(&mainWindow))
	{
		///Start drawing
		glClearColor(0.2f,0.3f,0.3f,0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		useShader(&shaderProgram);
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue)/2.0f + 0.5f;
		//printf("Green Value: %f\n",greenValue);
		int modifiedColor = glGetUniformLocation(shaderProgram,"modifiedColor");
		glUniform4f(modifiedColor,0.0f,greenValue,0.0f,1.0f);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES,0,sizeof(vertices));
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		//Change frame
		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}

	stopWindow(&mainWindow);

	//VAOS AND VBOS
	glDeleteVertexArrays(1,&VAO);
    	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	deleteShaderProgram(&shaderProgram);

	glfwTerminate();

	exit(0);
}


void frame_buffer_size_callback(GLFWwindow* w,int width,int height)
{
	glViewport(0,0,width,height);
}
