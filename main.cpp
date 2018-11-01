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
#include "Engine/PointLight.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SpotLight.h"

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

	//create material
	const Maths::Vector3 mEC = Maths::Vector3(0.0f, 0.0f, 0.0f);
	const Maths::Vector3 mAC = Maths::Vector3(1, 1, 1);
	const Maths::Vector4 mDC = Maths::Vector4(1, 1, 1, 1);
	const Maths::Vector3 mSC = Maths::Vector3(1, 1, 1);
	const float mSE = 80.0f;
	const Maths::Vector3 lADS = Maths::Vector3(1, 1, 1);
	Material material(mEC, mAC, mDC, mSC, mSE, lADS);

	//Load Models
	Model monkey("Assets/Model/Monkey.obj");
	Model cube("Assets/Model/cube.obj");
	Model ground("Assets/Model/Floor.obj");

	//Shader
	Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragment.glsl", 1, 2, 1);

	//Camera
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 10, 20, false);

	//Lights
	PointLight light(1.0f, Maths::Vector3(1, 1, 1), Maths::Vector3(0, 0, 0.1f));
	PointLight light2(1.0f, Maths::Vector3(1, 0, 1), Maths::Vector3(0, 0, 0.1f));
	light.translate(Maths::Vector3(0, 4, 5), true);
	light2.translate(Maths::Vector3(0, 4, -5), true);
	DirectionalLight dirlight(0.1f, Maths::Vector3(1, 1, 1));
	dirlight.translate(0,0,1, true);
	SpotLight spotlight(1.0f, Maths::Vector3(1, 0.5f, 0.2f), Maths::Vector3(0, 0.1f, 0.1f), Maths::Vector3(0, 0, -1), 0.5f, 40.0f);
	camera.addChild((Object *)&spotlight);

	//Objects
	Object monkeyObj;
	monkeyObj.addComponent((Component *)new ModelRenderer(&monkey, &material, &shader));
	monkeyObj.translate(Maths::Vector3(0, 3, 0), true);
	Object groundObj;
	groundObj.addComponent((Component *)new ModelRenderer(&ground, &material, &shader));
	groundObj.scale(Maths::Vector3(100, 1, 100));

	long starttime = Time::time();
	int framecount = 0;
	while (window.running)
	{
		//update fps counter
		if (Time::time() - starttime >= 1000)
		{
			starttime = Time::time();
			std::cout << framecount << std::endl;
			framecount = 0;
		}

		//check for errors
		if (checkGLError())
			return -1;

		//reset the window
		window.clear();

		//set up the shader
		shader.use();
		shader.setMat4("view_matrix", camera.Transform());
		shader.setMat4("proj_matrix", camera.Projection());
		light.setShader(&shader, camera, 0);
		light2.setShader(&shader, camera, 1);
		dirlight.setShader(&shader, camera, 0);
		spotlight.setShader(&shader, camera, 0);

		//draw the objects
		shader.setMat4("model_matrix", monkeyObj.Transform());
		monkeyObj.update();
		shader.setMat4("model_matrix", groundObj.Transform());
		groundObj.update();

		//handle the input
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if (Input::isKeyDown(GLFW_KEY_W))
		{
			camera.translate(Maths::Vector3(0, 0, -10) * Time::deltatime(), false);
		}
		if (Input::isKeyDown(GLFW_KEY_A))
		{
			camera.translate(Maths::Vector3(-10, 0, 0) * Time::deltatime(), false);
		}
		if (Input::isKeyDown(GLFW_KEY_S))
		{
			camera.translate(Maths::Vector3(0, 0, 10) * Time::deltatime(), false);
		}
		if (Input::isKeyDown(GLFW_KEY_D))
		{
			camera.translate(Maths::Vector3(10, 0, 0) * Time::deltatime(), false);
		}
		if (Input::isKeyDown(GLFW_KEY_SPACE))
		{
			camera.translate(Maths::Vector3(0, 10, 0) * Time::deltatime(), false);
		}
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			camera.translate(Maths::Vector3(0, -10, 0) * Time::deltatime(), false);
		}

		if (Input::mouseDragged())
			camera.turn(Input::mouseDragX() / 3.0f, Input::mouseDragY() / 3.0f);

		if (Input::isKeyPressed(GLFW_KEY_F11))
		{
			std::cout << "Switch fullscreen" << std::endl;
			window.fullscreen(!window.isFullscreen());
		}

		//update the pointlight
		// monkeyObj.rotate(Maths::Quaternion::fromAxisAngle(20 * Time::deltatime(), Maths::Vector3(0,1,0)));
		light.translate(Maths::Vector3(5.0f * Time::deltatime(), 0, 0), false);
		light2.translate(Maths::Vector3(1.0f * Time::deltatime(), 0, 0), false);
		light.lookAt(Maths::Vector3(0, 4, 0));
		light2.lookAt(Maths::Vector3(0, 4, 0));

		//update the window
		if (window.isfocused)
			window.setCurrent();
		window.update();
		framecount++;
	}

	FreeImage_DeInitialise();
	return 0;
}