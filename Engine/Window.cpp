#include "Window.h"

Window::Window(const char* name, int width, int height):
	name(name),
	width(width),
	height(height),
	input(new Input())
{
}

// WINDOW CALLBACKS
void errorCallback(int code , const char * description){
	std::cout << "GLFW ERROR: " << code << " - " << description;
}
void windowKeyChange(GLFWwindow* win, int key, int scancode, int action, int mods) {

	Window* window = (Window*)glfwGetWindowUserPointer(win);
	Input* input = window->input;
	switch (action) {
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

void mouseMoved(GLFWwindow* win, double x, double y){
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	window->input->setMouse(x, y);
}


void windowResized(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
}

void windowFocusChange(GLFWwindow* win, int focused){
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if(focused == GLFW_TRUE){
		window->isfocused = true;
		window->input->focus();
	}else{
		window->isfocused = false;
	}
}

bool Window::init() {
	return init(NULL);
}
bool Window::init(Window* parent) {
	/* Initialize the library */
	if (!glfwInit())
		std::cout << "ERROR: Failed to initialize glfw" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* p = NULL;
	if (parent != NULL) {
		p = parent->getContext();
	}
	window = glfwCreateWindow(width, height, name, NULL, p);
	if (!window)
	{
		std::cout << "ERROR: Failed to create OpenGl context" << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
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
	std::cout << "Intialized with openGL version: " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::setCurrent() {
		glfwMakeContextCurrent(window);
}

void Window::focus() {
		glfwFocusWindow(window);
}
void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() {

		input->update();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		running = !glfwWindowShouldClose(window);
}

void Window::close() {
	glfwSetWindowShouldClose(window, true);
}

Window::~Window() {
	glfwTerminate();
}