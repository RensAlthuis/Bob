#include "Window.h"

Window::Window(const char* name, int width, int height):
	name(name),
	width(width),
	height(height),
	input(new Input())
{
}

// WINDOW CALLBACKS
void windowResized(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
}

void windowKeyChange(GLFWwindow* win, int key, int scancode, int action, int mods) {

	Window* window = (Window*)glfwGetWindowUserPointer(win);
	Input* input = window->input;
	switch (action) {
	case GLFW_PRESS:
		input->press(key);
		break;
	case GLFW_RELEASE:
		input->release(key);
		break;
	case GLFW_REPEAT:
		input->repeat(key);
		break;
	}
}

void windowFocusChange(GLFWwindow* win, int focused){
	if(focused == GLFW_TRUE){
		std::cout << "setFocus" << std::endl;
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		window->input->focus();
	}
}

bool Window::init() {
	/* Initialize the library */
	if (!glfwInit())
		std::cout << "ERROR: Failed to initialize glfw" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, name, NULL, NULL);
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
	glfwSetWindowFocusCallback(window, windowFocusChange);
	std::cout << "Intialized with openGL version: " << glGetString(GL_VERSION) << std::endl;
	return true;
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