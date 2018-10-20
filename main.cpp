#define FREEIMAGE_LIB
#include <stdlib.h>
#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Texture.h"
#include "Engine/Maths/Maths.h"
#include "Engine/Time.h"
#include "Engine/Material.h"
#include "Engine/ModelRenderer.h"

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
	Window window("Squash", WIDTH, HEIGHT, false);
	if (!window.init())
		return -1;

	const Maths::Vector3 mEC = Maths::Vector3(0.0f, 0.0f, 0.0f);
	const Maths::Vector3 mAC = Maths::Vector3(1, 1, 1);
	const Maths::Vector4 mDC = Maths::Vector4(0, 1, 1, 1);
	const Maths::Vector3 mSC = Maths::Vector3(1, 1, 1);
	const float mSE = 80.0f;
	const Maths::Vector3 lADS = Maths::Vector3(1, 1, 1);
	Material material(mEC, mAC, mDC, mSC, mSE, lADS);

	//Load Models
	Model monkey("Assets/Model/Monkey.obj");
	Model cube("Assets/Model/cube.obj");
	Model ground("Assets/Model/Floor.obj");

	//Shader
	Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragment.glsl");

	//Camera
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 10, 20, false);

	//Light
	Object light;
	light.translate(Maths::Vector3(0, 5, 5), false);
	light.scaleAll(0.2);

	Object monkeyObj;
	monkeyObj.addComponent((Component*)new ModelRenderer(&monkey, &material, &shader));
	Object groundObj;
	groundObj.addComponent((Component*) new ModelRenderer(&ground, &material, &shader));

	const int nMonkeys = 1;
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
		int pointLightCount = 2;

		const Maths::Vector4 plp[] = {Maths::Vector4(light.translation.x, light.translation.y, light.translation.z, 1) * camera.Transform(),
										Maths::Vector4(-light.translation.x, light.translation.y, -light.translation.z, 1) * camera.Transform()};
		const Maths::Vector3 pla[] = {Maths::Vector3(0, 0, 0.1f), Maths::Vector3(0, 0, 0.1f)};
		const float pli[] = {1.0f, 1.0f};
		const Maths::Vector3 plc[] = {Maths::Vector3(1, 0.6, 0.3), Maths::Vector3(1, 1, 1)};

		shader.use();
		shader.setMat4("view_matrix", camera.Transform());
		shader.setMat4("proj_matrix", camera.Projection());

		shader.setInt1("pointLightCount", pointLightCount);
		shader.setVec4Arr("pointLightPos", plp, pointLightCount);
		shader.setFloatArr("pointLightIntensity", pli, pointLightCount);
		shader.setVec3Arr("pointLightColour", plc, pointLightCount);
		shader.setVec3Arr("pointLightAttenuation", pla, pointLightCount);

		for (int i = 0; i < nMonkeys; i++)
		{
			for (int j = 0; j < nMonkeys; j++)
			{
				Maths::Matrix4 model = Maths::Matrix4::translate(2 * i - nMonkeys + 1, 2 * j + 1, 0) * Maths::Matrix4::scale(0.8f, 0.8f, 0.8f);
				shader.setMat4("model_matrix", model);
				monkeyObj.update();
			}
		}

		shader.setMat4("model_matrix", Maths::Matrix4::scale(100, 1, 100));
		groundObj.update();

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