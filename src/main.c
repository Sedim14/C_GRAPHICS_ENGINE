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

	glfwSetFramebufferSizeCallback(mainWindow.window,frame_buffer_size_callback);
	glViewport(0,0,mainWindow.width,mainWindow.height);//Set and start the rendering window for the current window that has been created

	while(windowIsOpen(&mainWindow))
	{
		glClearColor(0.2f,0.3f,0.3f,0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}

	stopWindow(&mainWindow);

	glfwTerminate();

	exit(0);
}


void frame_buffer_size_callback(GLFWwindow* w,int width,int height)
{
	glViewport(0,0,width,height);
}
