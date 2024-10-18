#include<glad/glad.h>
#include "window.h"

bool startWindow(Window *w)
{
	w->window = glfwCreateWindow(w->width,w->height,w->name,NULL,NULL);
	if(w->window)
	{
		glfwMakeContextCurrent(w->window);
		return true;
	}
	else
		return false;
}



bool windowIsOpen(Window *w)
{
	if(!glfwWindowShouldClose(w->window))
		return true;
	else
		return false;
	
}

void stopWindow(Window *w)
{
	glfwDestroyWindow(w->window);
}

void setWindowVersion(int version)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,version);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
}
