#include "Window.h"

Window::Window() {
}

bool Window::init() {
	/* Initialize the library */
	if (!glfwInit())
		std::cout << "ERROR couldn't initialize glfw" << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR: couldn't create OpenGl context" << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR coudn't init glew" << std::endl;
		return false;
	}

	close = false;

	std::cout << "Intialized with openGL version: " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() {

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		close = glfwWindowShouldClose(window);
}

Window::~Window() {
	glfwTerminate();
}