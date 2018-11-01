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
	Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragmenttest.glsl", 0,1,0);

	//Camera
	Camera camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera.translate(0, 10, 20, false);

	//Lights
	PointLight light(1.0f, Maths::Vector3(1, 0.6, 0.3), Maths::Vector3(0, 0, 0.1f));
	light.translate(Maths::Vector3(0, 4, 5), false);
	DirectionalLight dirlight(1.0f, Maths::Vector3(1, 0.6, 0.3));
	SpotLight spotlight(1.0f, Maths::Vector3(1,1,1), Maths::Vector3(0, 0, 0.1f), Maths::Vector3(0,0,-1), 1.0f, 1.0f);
	// camera.addChild((Object*)&spotlight);

	float *pli = new float[1];
	Maths::Vector3 *plc = new Maths::Vector3[1];
	Maths::Vector3 *plp = new Maths::Vector3[1];
	Maths::Vector3 *pla = new Maths::Vector3[1];
	float *dli = new float[1];
	Maths::Vector3 *dlc = new Maths::Vector3[1];
	Maths::Vector3 *dlp = new Maths::Vector3[1];
	float *sli = new float[1];
	Maths::Vector3 *slp = new Maths::Vector3[1];
	Maths::Vector3 *slc = new Maths::Vector3[1];
	Maths::Vector3 *sla = new Maths::Vector3[1];
	Maths::Vector3 *sld = new Maths::Vector3[1];
	float *slangle = new float[1];
	float *slexp = new float[1];

	dli[0] = dirlight.intensity;
	dlc[0] = dirlight.colour;
	pli[0] = light.intensity;
	plc[0] = light.colour;
	pla[0] = light.attenuation;
	sli[0] = spotlight.intensity;
	slc[0] = spotlight.colour;
	sla[0] = spotlight.attenuation;
	sld[0] = spotlight.direction;
	slangle[0] = spotlight.angle;
	slexp[0] = spotlight.exponent;
			   
	//Objects
	Object monkeyObj;
	monkeyObj.addComponent((Component *)new ModelRenderer(&monkey, &material, &shader));
	monkeyObj.translate(Maths::Vector3(0,3,0), true);
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

		dlp[0] = dirlight.translation*camera.Transform();
		plp[0] = light.translation*camera.Transform();
		slp[0] = spotlight.translation*camera.Transform();
		//set up the shader
		shader.use();
		shader.setVec3Arr("pointLightPos", plp, 1);
		shader.setFloatArr("pointLightIntensity", pli, 1);
		shader.setVec3Arr("pointLightColour", plc, 1);
		shader.setVec3Arr("pointLightAttenuation", pla, 1);
		shader.setVec3Arr("dirLightPos", dlp, 1);
		shader.setFloatArr("dirLightIntensity", dli, 1);
		shader.setVec3Arr("dirLightColour", dlc, 1);
		shader.setVec3Arr("spotLightPos", slp, 1);
		shader.setFloatArr("spotLightIntensity", sli, 1);
		shader.setVec3Arr("spotLightColour", slc, 1);
		shader.setVec3Arr("spotLightAttenuation", sla, 1);
		shader.setVec3Arr("spotLightDir", sld, 1);
		shader.setFloatArr("spotLightAngle", slangle, 1);
		shader.setFloatArr("spotLightExponent", slexp, 1);
		shader.setMat4("view_matrix", camera.Transform());
		shader.setMat4("proj_matrix", camera.Projection());

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

		//update the pointlight
		// monkeyObj.rotate(Maths::Quaternion::fromAxisAngle(20 * Time::deltatime(), Maths::Vector3(0,1,0)));
		light.translate(Maths::Vector3(5.0f * Time::deltatime(), 0, 0), true);
		light.lookAt(Maths::Vector3(0, 0, 0));

		//update the window
		if (window.isfocused)
			window.setCurrent();
		window.update();
		framecount++;
	}

	FreeImage_DeInitialise();
	return 0;
}