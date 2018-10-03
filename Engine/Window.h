#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"

class Window
{
  private:
	GLFWwindow *window;
	const char *name;
	int width;
	int height;
	int resolutionX;
	int resolutionY;
	Window* parent;
	bool _isFullscreen;

  public:
	Input *input;
	bool isfocused;
	bool running;

	private:
	bool createWindow();

  public:
	Window(const char *name, int width, int height, bool isFullscreen);
	~Window();
	GLFWwindow *getContext() { return window; };
	bool init();
	void fullscreen(bool value);
	bool init(Window *parent);
	void clear();
	void update();
	void setCurrent();
	void focus();
	void close();
	bool isFullscreen(){return _isFullscreen;};
};