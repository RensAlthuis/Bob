#include "Window.h"

namespace Engine
{
Window::Window(const char *name, int width, int height, bool isFullscreen)
	: name(name), width(width), height(height), input(new Input()), window(NULL), _isFullscreen(isFullscreen), lastFrameTime(Time::time()), framecount(0), frametime(0), framestart(Time::time())
{
}

// WINDOW CALLBACKS
void errorCallback(int code, const char *description)
{
	std::cout << "GLFW ERROR: " << code << " - " << description;
}
void windowKeyChange(GLFWwindow *win, int key, int scancode, int action, int mods)
{

	Window *window = (Window *)glfwGetWindowUserPointer(win);
	Input *input = window->input;
	switch (action)
	{
	case GLFW_PRESS:
		input->keysPressed[key] = true;
		input->keysDown[key] = true;
		break;
	case GLFW_RELEASE:
		input->keysReleased[key] = true;
		input->keysDown[key] = false;
		break;
	case GLFW_REPEAT:
		break;
	}
}

void mouseMoved(GLFWwindow *win, double x, double y)
{
	Window *window = (Window *)glfwGetWindowUserPointer(win);
	window->input->setMouse(x, y);
}

void windowResized(GLFWwindow *win, int w, int h)
{
	Window *window = (Window *)glfwGetWindowUserPointer(win);
	// window->resize(w,h);
}

void windowFocusChange(GLFWwindow *win, int focused)
{
	Window *window = (Window *)glfwGetWindowUserPointer(win);
	if (focused == GLFW_TRUE)
	{
		window->isfocused = true;
		window->input->focus();
	}
	else
	{
		window->isfocused = false;
	}
}

bool Window::init()
{
	return init(NULL);
}

bool Window::init(Window *_parent)
{

	parent = _parent;
	/* Initialize the library */
	if (!glfwInit())
		std::cout << "ERROR: Failed to initialize glfw" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!createWindow())
		return false;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
		return false;
	}
	running = true;

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, windowResized);
	glfwSetKeyCallback(window, windowKeyChange);
	glfwSetCursorPosCallback(window, mouseMoved);
	glfwSetWindowFocusCallback(window, windowFocusChange);
	glfwSetErrorCallback(errorCallback);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	glfwSwapInterval(0);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
	return true;
}

bool Window::createWindow()
{
	if (window != nullptr)
		glfwDestroyWindow(window);
	GLFWwindow *p = nullptr;
	if (parent != nullptr)
	{
		p = parent->getContext();
	}
	window = glfwCreateWindow(width, height, name, _isFullscreen ? glfwGetPrimaryMonitor() : NULL, p);
	if (!window)
	{
		std::cout << "ERROR: Failed to create OpenGl context" << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	GLFWmonitor *mon = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(mon);
	glfwSetWindowMonitor(window, NULL, mode->width - width, mode->height - height, width, height, mode->refreshRate);
	return true;
}

void Window::setCurrent()
{
	glfwMakeContextCurrent(window);
}

void Window::fullscreen(bool value)
{
	if (value == _isFullscreen)
		return;
	GLFWmonitor *mon = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(mon);
	if (value == true)
	{
		glfwSetWindowMonitor(window, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(window, NULL, mode->width - width, mode->height - height, width, height, mode->refreshRate);
	}
	_isFullscreen = value;
}

void Window::focus()
{
	glfwFocusWindow(window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{

	update_time();
	input->update();
	/* Swap front and back buffers */
	if (framestart != 0)
	{
		frametime = (Time::time() - framestart);
		framestart = 0;
	}
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();

	running = !glfwWindowShouldClose(window);

	//update fps counter
	double t = Time::time();
	if (t - lastFrameTime >= 1)
	{
		lastFrameTime = t;
		fps = framecount;
		framecount = 0;

		std::cout << "FPS: " << fps << " , Frametime: " << frametime * 1000 << "ms" << std::endl;
		framestart = t;
	}
	framecount++;
}

int Window::Fps()
{
	return fps;
}

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}

void Window::update_time()
{
	double t = Time::time();
	Time::deltaTime = (t - Time::oldTime);
	Time::oldTime = t;
}

void Window::resize(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

Window::~Window()
{
	delete input;
	glfwTerminate();
}
}; // namespace Engine