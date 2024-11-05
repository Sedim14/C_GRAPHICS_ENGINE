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
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left
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
	unsigned int VBO, VAO, EBO, texture1, texture2;
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&EBO);
	glGenTextures(1,&texture1);
	glGenTextures(1,&texture2);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	/////Loading our textures
	
	//Texture1
	glActiveTexture(GL_TEXTURE0); //Accesung texture unit 0
	glBindTexture(GL_TEXTURE_2D,texture1);
	//Setting texture wrapping and filtering options
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
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
	
	//Texture2
	glActiveTexture(GL_TEXTURE1); //Accesung texture unit 1
	glBindTexture(GL_TEXTURE_2D,texture2);
	//Setting texture wrapping and filtering options
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load and generate the texture
	int width2, height2, nrChannels2;
	unsigned char *data2 = stbi_load("./TEXTURES/awesomeface.png",&width2,&height2,&nrChannels2,0);
	if(data2)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width2,height2,0,GL_RGBA,GL_UNSIGNED_BYTE,data2);
		glGenerateMipmap(GL_TEXTURE_2D);//RGBA is for reading images with alpha chanell correctly in opengl
	}
	else
	{
		printf("ERROR::Failed to load texture\n!!");
		exit(-1);
	}

	stbi_image_free(data2);


	/////////////////////////////
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
	
	//Using both shaders
	useShader(&shaderProgram);
	setInt(&shaderProgram,0,"texture1");
	setInt(&shaderProgram,1,"texture2");

							   
							   

	while(windowIsOpen(&mainWindow))
	{
		///Start drawing
		glClearColor(0.2f,0.3f,0.3f,0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		useShader(&shaderProgram);

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
