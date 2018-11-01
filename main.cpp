#define FREEIMAGE_LIB
#include <stdlib.h>
#include <assert.h>
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

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

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

void genFrameBuf(unsigned int* buf, GLenum attachment, GLint format, GLenum type){
	glGenTextures(1, buf);
	glBindTexture(GL_TEXTURE_2D, *buf);
	glTexImage2D(GL_TEXTURE_2D, 0, format, WIDTH, HEIGHT, 0, type, GL_FLOAT, nullptr);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, *buf, 0);
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
	Shader geomShader("Assets/Shader/vertexdef.glsl", "Assets/Shader/fragmentdef.glsl", 0, 0, 0);
	Shader lightShader("Assets/Shader/vertexdeflight.glsl", "Assets/Shader/fragmentdeflight.glsl", 1, 2, 1);

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
	monkeyObj.addComponent((Component *)new ModelRenderer(&monkey, &material, &geomShader));
	monkeyObj.translate(Maths::Vector3(0, 3, 0), true);
	Object groundObj;
	groundObj.addComponent((Component *)new ModelRenderer(&ground, &material, &geomShader));
	groundObj.scale(Maths::Vector3(100, 1, 100));

	long starttime = Time::time();
	int framecount = 0;
	unsigned int gBuffer;
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	unsigned int gPos, gNorm, gDiff, gAmb, gSpec, gEm, gADS;
	genFrameBuf(&gPos, GL_COLOR_ATTACHMENT0, GL_RGB16F, GL_RGB);
	genFrameBuf(&gNorm, GL_COLOR_ATTACHMENT1, GL_RGB16F, GL_RGB);
	genFrameBuf(&gAmb, GL_COLOR_ATTACHMENT2, GL_RGB, GL_RGB);
	genFrameBuf(&gDiff, GL_COLOR_ATTACHMENT3, GL_RGB, GL_RGB);
	genFrameBuf(&gSpec, GL_COLOR_ATTACHMENT4, GL_RGBA, GL_RGBA);
	genFrameBuf(&gEm, GL_COLOR_ATTACHMENT5, GL_RGB, GL_RGB);
	genFrameBuf(&gADS, GL_COLOR_ATTACHMENT6, GL_RGB, GL_RGB);
	unsigned int attachments[7] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6};
	glDrawBuffers(7, attachments);
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
	lightShader.use();
	lightShader.setInt1("gPos", 0);
    lightShader.setInt1("gNorm", 1);
    lightShader.setInt1("gAmb", 2);
    lightShader.setInt1("gDiff", 3);
    lightShader.setInt1("gSpec", 4);
    lightShader.setInt1("gEm", 5);
    lightShader.setInt1("gADS", 6);
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
		geomShader.use();
		geomShader.setMat4("view_matrix", camera.Transform());
		geomShader.setMat4("proj_matrix", camera.Projection());

		//GEOMETRY PASS
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		geomShader.setMat4("model_matrix", monkeyObj.Transform());
		monkeyObj.update();
		geomShader.setMat4("model_matrix", groundObj.Transform());
		groundObj.update();

		//LIGHTINGPASS
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		lightShader.use();
		light.setShader(&lightShader, camera, 0);
		light2.setShader(&lightShader, camera, 1);
		dirlight.setShader(&lightShader, camera, 0);
		spotlight.setShader(&lightShader, camera, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gPos);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gNorm);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, gAmb);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, gDiff);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, gSpec);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, gEm);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, gADS);
		renderQuad();
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