#include "Window.h"

namespace Engine
{
Window::Window(const char *name, int width, int height, bool isFullscreen) : name(name),
																			 width(width),
																			 height(height),
																			 input(new Input()),
																			 window(NULL),
																			 _isFullscreen(isFullscreen)
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
	glViewport(0, 0, w, h);
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	glfwSwapInterval(0);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
	return true;
}

bool Window::createWindow()
{
	if (window != NULL)
		glfwDestroyWindow(window);
	GLFWwindow *p = NULL;
	if (parent != NULL)
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
	if (value == true)
	{
		GLFWmonitor *mon = glfwGetPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(mon);
		glfwSetWindowMonitor(window, mon, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}
	else
	{
		glfwSetWindowMonitor(window, NULL, 0, 0, width, height, GLFW_DONT_CARE);
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

	input->update();
	update_time();
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();

	running = !glfwWindowShouldClose(window);
}

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}

void Window::update_time()
{
	long t = Time::time();
	Time::deltaTime = (t - Time::oldTime) / 1000.0f;
	Time::oldTime = t;
}

Window::~Window()
{
	glfwTerminate();
}
}; // namespace Engine