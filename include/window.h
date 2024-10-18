#ifndef WINDOW_H
#define WINDOW_H

#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<stdbool.h>
//Header Files for Window Handling with glfw with simple sintaxes

typedef struct
{
	GLFWwindow *window;
	char *name;
	int width;
	int height;
}
Window;

bool startWindow(Window *w);
bool windowIsOpen(Window *w);
void stopWindow(Window *w);
void setWindowVersion(int version);

#endif
