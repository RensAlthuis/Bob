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
	bool running;
public:
	Window(const char* name, int width, int height);
	~Window();
	bool init();
	void clear();
	void update();
	void close();
};