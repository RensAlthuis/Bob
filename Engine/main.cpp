#include "Window.h"
#include "Shader.h"
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

int main(void)
{

	Window window("something", 1280, 720);

	if (!window.init())
	{
		return -1;
	}


	float vertices[] = {
		-0.5f, 0.5f,  0.0f,
		0.5f,  0.5f,  0.0f,
		0.5f,  -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		0, 2, 3    // second triangle
	};

	ElementBuffer* ebo = new ElementBuffer(indices, 6);

	VertexBuffer* vbo = new VertexBuffer(vertices, 12, 3);
	VertexArray* vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);

	//creating shader
	Shader shader("Shader/vertex.glsl", "Shader/fragment.glsl");

	// Maths::Matrix4 project = Maths::Matrix4::ortho(0, 16, 0, 9, -10, 10);
	Maths::Matrix4 project = Maths::Matrix4::perspective(90, 16.0f/9.0f, 0.03f, 10.0f);
	Maths::Matrix4 view = Maths::Matrix4::translate(0,0, -2.0f);
	Maths::Vector4 col(0.5f, 1.0f, 0.0f, 1.0f);
	int t = 0;

	// glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

	while (window.running)
	{
		// check OpenGL error
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
		// glClearColor(1,1,1,1);
		window.clear();

		//stuff here

		double mX, mY;
		Input::mousePos(mX, mY);
		shader.use();
		shader.setMat4("projection_matrix", project);
		shader.setMat4("view_matrix", view);
		shader.setVec4("col", col);
		shader.setVec2("mouse", Maths::Vector2(mX / 1280 * 16, 9-mY / 720 * 9));
		vao->bind();

		// Maths::Matrix4 offset = Maths::Matrix4::translate(8.0f, 4.5f, -1.0f);
		Maths::Matrix4 offset = Maths::Matrix4::translate(0, 0, 0);
		Maths::Matrix4 rot = Maths::Matrix4::rotate(t, 0, 1, 0) * Maths::Matrix4::rotate(30, 1, 0 ,0);
		Maths::Matrix4 scale = Maths::Matrix4::scale(2,2,2);
		Maths::Matrix4 transform = offset * rot * scale;

		//front
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0, 0, 0.5));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		//left
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0.5f, 0 ,0) * Maths::Matrix4::rotate(90, 0, 1, 0));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		//right
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(-0.5f, 0 ,0) * Maths::Matrix4::rotate(-90, 0, 1, 0));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		//back
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0, 0 ,-0.5f) * Maths::Matrix4::rotate(180, 0, 1, 0));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		//top
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0, 0.5f , 0) * Maths::Matrix4::rotate(90, 1, 0, 0));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		//bottom
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0, -0.5f ,0) * Maths::Matrix4::rotate(-90, 1, 0, 0));
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		if(Input::isKeyDown(GLFW_KEY_W))
			view = view * Maths::Matrix4::translate(0,0,0.1f);
		if(Input::isKeyDown(GLFW_KEY_A))
			view = view * Maths::Matrix4::translate(0.1f,0,0);
		if(Input::isKeyDown(GLFW_KEY_S))
			view = view * Maths::Matrix4::translate(0,0,-0.1f);
		if(Input::isKeyDown(GLFW_KEY_D))
			view = view * Maths::Matrix4::translate(-0.1f,0,0);

		t++;
		if (t > 360) t == 0;

		//end of stuff
		if(window.isfocused){
			window.setCurrent();
		}
		window.update();

	}

	return 0;
}