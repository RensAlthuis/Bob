#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"

class Window {
private:
	GLFWwindow* window;
	const char* name;
	int width;
	int height;

public:
	Input* input;
	bool isfocused;
	bool running;

public:
	Window(const char* name, int width, int height);
	~Window();
	GLFWwindow* getContext() { return window; };
	bool init();
	bool init(Window* parent);
	void clear();
	void update();
	void setCurrent();
	void focus();
	void close();
};