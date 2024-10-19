#include<glad/glad.h>
#include<stdlib.h>
#include<GLFW/glfw3.h>
#include<stdbool.h>
#include"window.h"
#include"shader.h"

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
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
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


	//lOAD VBOS AND VAOS
	unsigned int VBO, VAO;
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glfwSetFramebufferSizeCallback(mainWindow.window,frame_buffer_size_callback);
	glViewport(0,0,mainWindow.width,mainWindow.height);//Set and start the rendering window for the current window that has been created

	while(windowIsOpen(&mainWindow))
	{
		///Start drawing
		glClearColor(0.2f,0.3f,0.3f,0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,sizeof(vertices));

		//Change frame
		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}

	stopWindow(&mainWindow);

	//VAOS AND VBOS
	glDeleteVertexArrays(1,&VAO);
    	glDeleteBuffers(1,&VBO);

	glfwTerminate();

	exit(0);
}


void frame_buffer_size_callback(GLFWwindow* w,int width,int height)
{
	glViewport(0,0,width,height);
}
