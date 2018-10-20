#define FREEIMAGE_LIB
#include <stdlib.h>
#include <assert.h>
#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Texture.h"
#include "Engine/Maths/Maths.h"
// #include "FreeImage.h"
#include "Engine/Time.h"

#define WIDTH 1280.0f
#define HEIGHT 720.0f

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
	Window window("Engine", WIDTH, HEIGHT, false);
	if (!window.init())
		return -1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	Model monkey("Assets/Model/cube.obj");
	Model cube("Assets/Model/cube.obj");
	Model ground("Assets/Model/Floor.obj");
	Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragment.glsl");
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 10, 20, false);
	Object light;
	light.translate(Maths::Vector3(0, 5, 5), false);
	light.scaleAll(0.2);

	const int nMonkeys = 10;
	float *cols = new float[3 * nMonkeys * nMonkeys];
	for (int i = 0; i < nMonkeys; i++)
	{
		for (int j = 0; j < nMonkeys; j++)
		{
			cols[i * nMonkeys + j + 0] = (float)(rand() % 255) / 255;
			cols[i * nMonkeys + j + 1] = (float)(rand() % 255) / 255;
			cols[i * nMonkeys + j + 2] = (float)(rand() % 255) / 255;
		}
	}
	long starttime = Time::time();
	int framecount = 0;
	while (window.running)
	{
		if (Time::time() - starttime >= 1000)
		{
			starttime = Time::time();
			std::cout << framecount << std::endl;
			framecount = 0;
		}

		if (checkGLError())
			return -1;
		window.clear();

		const Maths::Vector4 plp[] = {Maths::Vector4(light.translation.x, light.translation.y, light.translation.z, 1) * camera.Transform(),
									  Maths::Vector4(-light.translation.x, light.translation.y, -light.translation.z, 1) * camera.Transform()};
		const Maths::Vector3 pla[] = {Maths::Vector3(0, 0, 0.1f), Maths::Vector3(0, 0, 0.1f)};
		const float pli[] = {1.0f, 1.0f};
		const Maths::Vector3 plc[] = {Maths::Vector3(1, 0.6, 0.3), Maths::Vector3(1, 1, 1)};
		const Maths::Vector3 mEC = Maths::Vector3(0.0f, 0.0f, 0.0f);
		const Maths::Vector3 mAC = Maths::Vector3(1, 1, 1);
		const Maths::Vector4 mDC = Maths::Vector4(1, 1, 1, 1);
		const Maths::Vector3 mSC = Maths::Vector3(1, 1, 1);
		const float mSE = 80.0f;
		const Maths::Vector3 lADS[] = {Maths::Vector3(1, 1, 1), Maths::Vector3(1, 1, 1)};
		int pointLightCount = 2;

		shader.use();
		shader.setMat4("view_matrix", camera.Transform());
		shader.setMat4("proj_matrix", camera.Projection());

		shader.setInt1("pointLightCount", pointLightCount);
		shader.setVec4Arr("pointLightPos", plp, pointLightCount);
		shader.setFloatArr("pointLightIntensity", pli, pointLightCount);
		shader.setVec3Arr("pointLightColour", plc, pointLightCount);
		shader.setVec3Arr("pointLightAttenuation", pla, pointLightCount);

		shader.setVec3("matEmissiveColour", mEC);
		shader.setVec3("matAmbiantColour", mAC);
		shader.setVec4("matDiffuseColour", mDC);
		shader.setVec3("matSpecularColour", mSC);
		shader.setFloat("matSpecularExp", mSE);
		shader.setVec3Arr("lightAmbDiffSpec", lADS, pointLightCount);

		// texture.bind();
		monkey.bind();
		assert(glGetError() == GL_NO_ERROR);
		for (int i = 0; i < nMonkeys; i++)
		{
			for (int j = 0; j < nMonkeys; j++)
			{
				// shader.setVec4("matDiffuseColour", Maths::Vector4(cols[i * nMonkeys + j + 0], cols[i * nMonkeys + j + 1], cols[i * nMonkeys + j + 2], 1));
				Maths::Matrix4 model = Maths::Matrix4::translate(2 * i - nMonkeys + 1, 2 * j + 1, 0);
				shader.setMat4("model_matrix", model * Maths::Matrix4::scale(0.8f, 0.8f, 0.8f));
				glDrawElements(GL_TRIANGLES, monkey.ElementCount(), GL_UNSIGNED_INT, 0);
			}
		}

		ground.bind();
		shader.setVec4("matDiffuseColour", Maths::Vector4(1, 1, 1, 1));
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
			camera.turn(Input::mouseDragX() / 3.0f, Input::mouseDragY() / 3.0f);

		if (Input::isKeyPressed(GLFW_KEY_F11))
		{
			std::cout << "Switch fullscreen" << std::endl;
			window.fullscreen(!window.isFullscreen());
		}

		light.translate(Maths::Vector3(5.0f * Time::deltatime(), 0, 0), true);
		light.lookAt(Maths::Vector3(0, 10, 0));

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