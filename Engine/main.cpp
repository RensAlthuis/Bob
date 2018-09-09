#include "Window.h"
#include "FileReader.h"

int main(void)
{

	Window window("something", 800, 600);

	if (!window.init()) {
		return -1;
	}

	//creating vbo and sending it to the GPU
	GLfloat triangle[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0
	};

	GLuint vbo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	//set up vbo data for shader to use
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*) 0);
	glEnableVertexAttribArray(0);

	//creating shaders
	int  success;
	char infoLog[512];

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = readFile("Shader/vertex.glsl");
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR: failed to compile vertex shader\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = readFile("Shader/fragment.glsl");
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: failed to compile fragment shader\n" << infoLog << std::endl;
	}

	//creating shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: failed to link shader program\n" << infoLog << std::endl;
	}
	//linked shaders can be deleted
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//activate the shader program
	while (window.running)
	{
		window.clear();

		//stuff here

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		//end of stuff
		window.update();
	}

	return 0;
}