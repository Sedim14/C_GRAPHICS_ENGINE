#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdbool.h>
#include"window.h"

Window mainWindow =
{
	NULL,
	"Window",
	600,
	600
};

void frame_buffer_size_callback(GLFWwindow* w,int width,int height);

int main(int argv,char* argc[])
{	//This is commentary added to tost git
	glfwInit();
	setWindowVersion(3);

	if(!startWindow(&mainWindow))
		return -1;

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
       	{
          	printf("Failed to initialize GLAD\n");
	 	 return -1;
      	}

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

	return 0;
}


void frame_buffer_size_callback(GLFWwindow* w,int width,int height)
{
	glViewport(0,0,width,height);
}
