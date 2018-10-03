#define FREEIMAGE_LIB
#include <stdlib.h>
#include "Window.h"
#include "Shader.h"
#include "Maths/Maths.h"

#include "Texture.h"
#include "FreeImage.h"
#include "Model.h"
#include "Camera.h"

#define WIDTH 800.0f
#define HEIGHT 600.0f

bool checkGLError()
{
	// check OpenGL error
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL error: " << err << std::endl;
		return true;
	}
	return false;
}

int main(void)
{

	FreeImage_Initialise();
	Window window("something", WIDTH, HEIGHT);
	if (!window.init())
		return -1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Model monkey("Assets/Model/Monkey.obj");
	Model ground("Assets/Model/Floor.obj");
	Shader shader("Assets/Shader/vertexCol.glsl", "Assets/Shader/fragmentCol.glsl");
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 0, 2, false);

	float cols[300];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cols[i * 10 + j + 0] = (float)(rand() % 255) / 255;
			cols[i * 10 + j + 1] = (float)(rand() % 255) / 255;
			cols[i * 10 + j + 2] = (float)(rand() % 255) / 255;
		}
	}

	float t = 0;

	while (window.running)
	{
		if (checkGLError())
			return -1;
		window.clear();

		shader.use();
		shader.setMat4("projection_matrix", camera.Projection());
		shader.setMat4("view_matrix", camera.Transform());
		// shader.setVec4("lightCol", Maths::Vector4(0.8f, 0.3f, 0.2f, 1));
		shader.setVec4("lightCol", Maths::Vector4(1,1,1, 1));
		shader.setVec3("lightPos", Maths::Vector3(0, 0, 1.0f));
		Maths::Vector3 dir(cos(t), -0.3f, sin(t));
		dir = dir / dir.length();
		shader.setVec3("directionallight", dir);
		t += 0.01;
		if (t >= 360)
			t = 0;

		// texture.bind();
		monkey.bind();
		// vao->bind();
		const int nMonkeys = 10;
		for (int i = 0; i < nMonkeys; i++)
		{
			for (int j = 0; j < nMonkeys; j++)
			{
				shader.setVec4("colour", Maths::Vector4(cols[i * nMonkeys + j + 0], cols[i * nMonkeys + j + 1], cols[i * nMonkeys + j + 2], 1));
				Maths::Matrix4 model = Maths::Matrix4::translate(2 * i - nMonkeys + 1, 2 * j + 1, 0);
				shader.setMat4("model_matrix", model * Maths::Matrix4::scale(0.8f, 0.8f, 0.8f));
				// shader.setVec4("colour", Maths::Vector4(1,1,1,1));
				// shader.setMat4("model_matrix", Maths::Matrix4::identity());
				glDrawElements(GL_TRIANGLES, monkey.ElementCount(), GL_UNSIGNED_INT, 0);
			}
		}

		ground.bind();
		shader.setVec4("colour", Maths::Vector4(1,1,1,1));
		shader.setMat4("model_matrix", Maths::Matrix4::scale(100, 1, 100));
		glDrawElements(GL_TRIANGLES, ground.ElementCount(), GL_UNSIGNED_INT, 0);

		// Maths::Vector3 front = camera.Front();
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if (Input::isKeyDown(GLFW_KEY_W))
		{
			camera.translate(0, 0, -0.1f, true);
		}
		if (Input::isKeyDown(GLFW_KEY_A))
		{
			camera.translate(-0.1f, 0, 0, true);
		}
		if (Input::isKeyDown(GLFW_KEY_S))
		{
			camera.translate(0, 0, 0.1f, true);
		}
		if (Input::isKeyDown(GLFW_KEY_D))
		{
			camera.translate(0.1f, 0, 0, true);
		}
		if (Input::isKeyDown(GLFW_KEY_SPACE))
		{
			camera.translate(0, 0.1f, 0, true);
		}
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			camera.translate(0, -0.1f, 0, true);
		}

		// camera.lookAt(Maths::Vector3(0, 0, 0));
		if (Input::mouseDragged())
			camera.turn(Input::mouseDragX(), Input::mouseDragY());
		//end of stuff

		if (window.isfocused)
			window.setCurrent();
		window.update();
	}
	FreeImage_DeInitialise();
	return 0;
}