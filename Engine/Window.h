#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* window;

public:
	bool close;
public:
	Window();
	~Window();
	bool init();
	void clear();
	void update();
};