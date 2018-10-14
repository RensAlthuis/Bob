#define FREEIMAGE_LIB
#include <stdlib.h>
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Maths/Maths.h"
#include "FreeImage.h"
#include "Time.h"

#define WIDTH 800.0f
#define HEIGHT 600.0f

using namespace Engine;

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
	Window window("Bob", WIDTH, HEIGHT, false);
	if (!window.init())
		return -1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	Model monkey("Assets/Model/Monkey.obj");
	Model ground("Assets/Model/Floor.obj");
	Shader shader("Assets/Shader/vertexCol.glsl", "Assets/Shader/fragmentCol.glsl");
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 10, 20, false);

	const int nMonkeys = 100;
	float* cols = new float[3*nMonkeys*nMonkeys];
	for (int i = 0; i < nMonkeys; i++)
	{
		for (int j = 0; j < nMonkeys; j++)
		{
			cols[i * nMonkeys + j + 0] = (float)(rand() % 255) / 255;
			cols[i * nMonkeys + j + 1] = (float)(rand() % 255) / 255;
			cols[i * nMonkeys + j + 2] = (float)(rand() % 255) / 255;
		}
	}
	float t = 0;
	long starttime = Time::time();
	int framecount=0;
	Object light;
	light.translate(Maths::Vector3(0,10,10),false);
	while (window.running)
	{
		if(Time::time() - starttime >= 1000){
			starttime = Time::time();
			std::cout << framecount << std::endl;
			framecount = 0;
		}

		if (checkGLError())
			return -1;
		window.clear();

		shader.use();
		shader.setMat4("pv_matrix", camera.Projection() * camera.Transform());

		Maths::Vector3 dir(cos(t), -0.3f, sin(t));
		dir.normalize();
		shader.setVec3("directionallight", dir);
		shader.setVec4("lightCol", Maths::Vector4(0.0f, 0.0f, 0.0f, 1));

		shader.setVec3("pointlight", light.translation);
		shader.setFloat1("pointIntensity", 8.0f);
		light.translate(Maths::Vector3(5.0f * Time::deltatime(), 0, 0), true);
		light.lookAt(Maths::Vector3(0,10,0));

		t += 0.01;
		if (t >= 360)
			t = 0;

		// texture.bind();
		monkey.bind();
		for (int i = 0; i < nMonkeys; i++)
		{
			for (int j = 0; j < nMonkeys; j++)
			{
				shader.setVec4("colour", Maths::Vector4(cols[i * nMonkeys + j + 0], cols[i * nMonkeys + j + 1], cols[i * nMonkeys + j + 2], 1));
				Maths::Matrix4 model = Maths::Matrix4::translate(2 * i - nMonkeys + 1, 2 * j + 1, 0);
				shader.setMat4("model_matrix", model * Maths::Matrix4::scale(0.8f, 0.8f, 0.8f));
				glDrawElements(GL_TRIANGLES, monkey.ElementCount(), GL_UNSIGNED_INT, 0);
			}
		}

		ground.bind();
		shader.setVec4("colour", Maths::Vector4(1,1,1,1));
		shader.setMat4("model_matrix", Maths::Matrix4::scale(100, 1, 100));
		glDrawElements(GL_TRIANGLES, ground.ElementCount(), GL_UNSIGNED_INT, 0);

		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if (Input::isKeyDown(GLFW_KEY_W))
		{
			camera.translate(Maths::Vector3(0, 0, -10) * Time::deltatime(), true);
		}
		if (Input::isKeyDown(GLFW_KEY_A))
		{
			camera.translate(Maths::Vector3(-10, 0, 0) * Time::deltatime(), true);
		}
		if (Input::isKeyDown(GLFW_KEY_S))
		{
			camera.translate(Maths::Vector3(0, 0, 10) * Time::deltatime(), true);
		}
		if (Input::isKeyDown(GLFW_KEY_D))
		{
			camera.translate(Maths::Vector3(10, 0, 0) * Time::deltatime(), true);
		}
		if (Input::isKeyDown(GLFW_KEY_SPACE))
		{
			camera.translate(Maths::Vector3(0, 10, 0) * Time::deltatime(), true);
		}
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			camera.translate(Maths::Vector3(0, -10, 0) * Time::deltatime(), true);
		}

		if (Input::mouseDragged())
			camera.turn(Input::mouseDragX()/3.0f, Input::mouseDragY()/3.0f);

		if(Input::isKeyPressed(GLFW_KEY_F11))
		{
			std::cout << "Switch fullscreen" << std::endl;
			window.fullscreen(!window.isFullscreen());
		}
		//end of stuff

		if (window.isfocused)
			window.setCurrent();
		window.update();
		framecount++;
	}
	FreeImage_DeInitialise();
	delete[] cols;
	return 0;
}