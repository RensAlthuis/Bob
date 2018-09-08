#include "Window.h"

int main(void)
{


	Window window;
	if (!window.init()) {
		return -1;
	}
	GLuint vao;

	/* Loop until the user closes the window */
	while (!window.close)
	{
		window.clear();
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
		window.update();
	}

	return 0;
}