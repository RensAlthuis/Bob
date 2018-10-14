#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"
#include "Time.h"


namespace Engine{
class Window
{
  private:
	const char *name;
	int width;
	int height;
	int resolutionX;
	int resolutionY;
	Window* parent;
	bool _isFullscreen;

  public:
	GLFWwindow *window;
	Input *input;
	bool isfocused;
	bool running;

	private:
	bool createWindow();
	void update_time();

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
	void resize(int w, int h);
};
};