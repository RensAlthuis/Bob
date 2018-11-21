#define FREEIMAGE_LIB
#include <stdlib.h>
#include <assert.h>
#include "Engine/Maths/Maths.h"
#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Engine/Texture.h"
#include "Engine/Time.h"
#include "Engine/ModelRenderer.h"
#include "Engine/Buffer/FrameBuffer.h"

#include "Engine/PointLight.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SpotLight.h"

#include "Engine/ECS/ECSManager.h"
#include "Engine/Material.h"
#include "Engine/Model.h"
#include "Engine/Transform.h"

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
			-1.0f,
			1.0f,
			0.0f,
			0.0f,
			1.0f,
			-1.0f,
			-1.0f,
			0.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			0.0f,
			1.0f,
			1.0f,
			1.0f,
			-1.0f,
			0.0f,
			1.0f,
			0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
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

void handleInput(Window &window, Camera &camera)
{
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
}

struct TransformComponent : public ECS::Component<TransformComponent>
{
	TransformComponent *Parent;
	Transform transform;
};

struct RenderComponent : public ECS::Component<RenderComponent>
{
	Material* mat;
	Shader* shader;
};

struct rotateFlag: public ECS::Component<rotateFlag> {
	float speed;
};

class TestSystem : public ECS::System
{
  public:
	TestSystem() : System()
	{
		addComponentType(TransformComponent::TYPE);
		addComponentType(rotateFlag::TYPE);
	};
	void update(float deltaTime, ECS::IComponent **components) const override
	{
		TransformComponent *comp0 = (TransformComponent *)components[0];
		rotateFlag *comp1 = (rotateFlag*)components[1];
		comp0->transform.rotate(Maths::Quaternion::fromAxisAngle(deltaTime * comp1->speed, 0, 1, 0));
	};
};

class RenderSystem : public ECS::System
{
	public:
	RenderSystem() : System()
	{
		addComponentType(TransformComponent::TYPE);
		addComponentType(RenderComponent::TYPE);
		addComponentType(Model::TYPE);
	}

	void update(float deltaTime, ECS::IComponent **components) const override
	{
		//transform
		TransformComponent *transform = (TransformComponent*)components[0];
		RenderComponent *render = (RenderComponent*)components[1];
		Model *model= (Model*)components[2];

		model->bind();
		render->shader->setMat4("model_matrix", transform->transform.Matrix());
		setMaterial(render);
		glDrawElements(GL_TRIANGLES, model->ElementCount(), GL_UNSIGNED_INT, 0);
	}

	void setMaterial(RenderComponent* render) const
	{
		Shader* shader = render->shader;
		Material* mat = render->mat;
		shader->setVec3("matEmissiveColour", mat->mEC);
		shader->setVec3("matAmbiantColour", mat->mAC);
		shader->setVec3("matDiffuseColour", Maths::Vector3(mat->mDC.x, mat->mDC.y, mat->mDC.z));
		shader->setVec3("matSpecularColour", mat->mSC);
		shader->setFloat("matSpecularExp", mat->mSE);
		shader->setVec3("lightAmbDiffSpec", mat->lADS);
	}
};

int main(void)
{

	// FreeImage_Initialise();
	Window window("Engine", WIDTH, HEIGHT, false);
	if (!window.init())
		return -1;


	ECS::ECSManager ecs;
	TestSystem sys;
	RenderSystem rendersys;
	ECS::SystemGroup testGroup;
	ECS::SystemGroup renderGroup;
	testGroup.addSystem(&sys);
	renderGroup.addSystem(&rendersys);


	//create material
	Material* mat = new Material();
	mat->mEC = Maths::Vector3(0.0f, 0.0f, 0.0f);
	mat->mAC = Maths::Vector3(1, 1, 1);
	mat->mDC = Maths::Vector4(1, 1, 1, 1);
	mat->mSC = Maths::Vector3(1, 1, 1);
	mat->mSE = 80.0f;
	mat->lADS = Maths::Vector3(1, 1, 1);

	//Load Models
	Model *monkey = new Model("Assets/Model/MonkeySmooth.obj");
	Model *cube = new Model("Assets/Model/cube.obj");
	Model *ground = new Model("Assets/Model/Floor.obj");

	//Shader
	Shader *geomShader = new Shader("Assets/Shader/vertexdef.glsl", "Assets/Shader/fragmentdef.glsl", 0, 0, 0);
	Shader *lightShader = new Shader("Assets/Shader/vertexdeflight.glsl", "Assets/Shader/fragmentdeflight.glsl", 1, 2, 1);

	//Camera
	Camera* camera = new Camera(60, WIDTH / HEIGHT, 0.1f, 100);
	camera->translate(0, 10, 20, false);

	//Lights
	PointLight *light = new PointLight(1.0f, Maths::Vector3(1, 1, 1), Maths::Vector3(0, 0, 0.1f));
	PointLight *light2 = new PointLight(1.0f, Maths::Vector3(1, 0, 1), Maths::Vector3(0, 0, 0.1f));
	light->translate(Maths::Vector3(0, 4, 5), true);
	light2->translate(Maths::Vector3(0, 4, -5), true);
	DirectionalLight *dirlight = new DirectionalLight(0.1f, Maths::Vector3(1, 1, 1));
	dirlight->translate(0, 0, 1, true);
	SpotLight *spotlight = new SpotLight(1.0f, Maths::Vector3(1, 0.5f, 0.2f), Maths::Vector3(0, 0.1f, 0.1f), Maths::Vector3(0, 0, -1), 0.5f, 40.0f);
	camera->addChild(*spotlight);

	TransformComponent t1;
	t1.transform.scale(Maths::Vector3(100,1,100), true);
	TransformComponent t2;
	t2.transform.translate(0,3,0,true);
	rotateFlag r;
	r.speed = 10.0f;
	RenderComponent rend1;
	rend1.mat = mat;
	rend1.shader = geomShader;

	ECS::Entity* groundEntity = ecs.createEntity(ground, &rend1, &t1);
	ECS::Entity* monkeyEntity = ecs.createEntity(monkey, &rend1, &t2, &r);

	//FrameBuffer
	FrameBuffer gBuffer(WIDTH, HEIGHT);
	gBuffer.bind();
	gBuffer.addTextureBuffer("gPos", GL_COLOR_ATTACHMENT0, GL_RGB16F, GL_RGB);
	gBuffer.addTextureBuffer("gNorm", GL_COLOR_ATTACHMENT1, GL_RGB16F, GL_RGB);
	gBuffer.addTextureBuffer("gEm", GL_COLOR_ATTACHMENT2, GL_RGB, GL_RGB);
	gBuffer.addTextureBuffer("gAmb", GL_COLOR_ATTACHMENT3, GL_RGB, GL_RGB);
	gBuffer.addTextureBuffer("gDiff", GL_COLOR_ATTACHMENT4, GL_RGB, GL_RGB);
	gBuffer.addTextureBuffer("gSpec", GL_COLOR_ATTACHMENT5, GL_RGBA, GL_RGBA);
	gBuffer.addTextureBuffer("gADS", GL_COLOR_ATTACHMENT6, GL_RGB, GL_RGB);
	gBuffer.setShader(*lightShader);
	gBuffer.unbind();

	while (window.running)
	{

		//check for errors
		if (checkGLError())
			return -1;

		//GEOMETRY PASS
		geomShader->use();
		geomShader->setMat4("view_matrix", camera->Transform());
		geomShader->setMat4("proj_matrix", camera->Projection());
		gBuffer.bind();
		window.clear();
		ecs.updateSystems(Time::deltatime(), renderGroup);
		gBuffer.unbind();

		//LIGHTINGPASS
		lightShader->use();
		light->setShader(lightShader, *camera, 0);
		light2->setShader(lightShader, *camera, 1);
		dirlight->setShader(lightShader, *camera, 0);
		spotlight->setShader(lightShader, *camera, 0);
		window.clear();
		gBuffer.bindTextures();
		renderQuad();

		handleInput(window, *camera);

		//update lights
		light->translate(Maths::Vector3(5.0f * Time::deltatime(), 0, 0), false);
		light2->translate(Maths::Vector3(1.0f * Time::deltatime(), 0, 0), false);
		light->lookAt(Maths::Vector3(0, 4, 0));
		light2->lookAt(Maths::Vector3(0, 4, 0));

		ecs.updateSystems(Time::deltatime(), testGroup);

		window.update();
	}

	// FreeImage_DeInitialise();
	return 0;
}