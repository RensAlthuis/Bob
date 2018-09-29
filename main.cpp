#define FREEIMAGE_LIB
#include "Window.h"
#include "Shader.h"
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "FreeImage.h"
#include "Model.h"

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

void GenCube(VertexArray *&vao, ElementBuffer *&ebo)
{
	float *vertices = new float[24 * 3]{
		1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,		//front face
		-1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1, -1, //back face
		1, 1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1,		//right face
		-1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1, //left face
		1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1,		//top face
		1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1  //bottom face
	};

	float *uvs = new float[24 * 3]{
		1, 1, 1, -1, -1, -1, -1, 1, //front
		1, 1, 1, -1, -1, -1, -1, 1, //back
		1, 1, 1, -1, -1, -1, -1, 1, //right
		1, 1, 1, -1, -1, -1, -1, 1, //left
		1, 1, 1, -1, -1, -1, -1, 1, //top
		1, 1, 1, -1, -1, -1, -1, 1, //bottom
	};
	unsigned int *indices = new unsigned int[3 * 12]{
		0, 3, 1, 2, 1, 3,		// front face
		4, 7, 5, 6, 5, 7,		// back face
		8, 11, 9, 10, 9, 11,	// right face
		12, 15, 13, 14, 13, 15, // left face
		16, 19, 17, 18, 17, 19, // top face
		20, 23, 21, 22, 21, 23, // bottom face

	};
	ebo = new ElementBuffer(indices, 3 * 12);
	VertexBuffer *vbo = new VertexBuffer(vertices, 24, 3);
	// VertexBuffer *ubo = new VertexBuffer(uvs, 24, 2);
	vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);
	// vao->addBuffer(ubo, 1);
}

void setUpShader(Shader *shader,
				 Maths::Matrix4 transform,
				 Maths::Matrix4 view,
				 Maths::Matrix4 project,
				 int t)
{
	shader->use();
	shader->setMat4("projection_matrix", project);
	shader->setMat4("view_matrix", view);
	shader->setMat4("model_matrix", transform * Maths::Matrix4::translate(0, 0, 0.0));
	shader->setVec4("lightCol", Maths::Vector4(1, 1, 1, 1));
	shader->setVec3("lightPos", Maths::Matrix4::rotate(0, 0, 1, 0) * Maths::Vector3(0, 0, -1.3f));
	shader->setVec4("colour", Maths::Vector4(1, 1, 1, 1));
	// shader->setInt1("tex", 0);
}

int main(void)
{

	FreeImage_Initialise();
	Window window("something", WIDTH, HEIGHT);
	if (!window.init())
		return -1;

	VertexArray *vao;
	ElementBuffer *ebo;
	// GenCube(vao, ebo);

	Model monkey("Assets/Model/Monkey.obj");
	int nverts, nnorms, nindices;
	float *verts;
	unsigned int *indices;
	monkey.Vertices(verts, nverts);
	monkey.Indices(indices, nindices);
	ebo = new ElementBuffer(indices, nindices);
	VertexBuffer *vbo = new VertexBuffer(verts, nverts, 3);
	vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);

	Shader shader("Assets/Shader/vertexCol.glsl", "Assets/Shader/fragmentCol.glsl");
	// Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragment.glsl");

	Texture texture("Assets/Img/leather.jpg");

	//Maths::Matrix4 project = Maths::Matrix4::ortho(0, 16, 0, 9, -10, 20);
	Maths::Matrix4 project = Maths::Matrix4::perspective(90, WIDTH / HEIGHT, 0.1f, 100.0f);
	Maths::Matrix4 view = Maths::Matrix4::translate(0, 0, -3.0f);

	int t = 0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	double mousex, mousey;
	Input::mousePos(mousex, mousey);
	double oldmousex = mousex;
	double oldmousey = mousey;
	double rotx, roty = 0;
	Maths::Vector3 camPos(0, 0 ,-3.0f);
	while (window.running)
	{
		Input::mousePos(mousex, mousey);
		if (checkGLError())
			return -1;

		window.clear();

		Maths::Matrix4 offset = Maths::Matrix4::translate(0, 0, 0);
		Maths::Matrix4 rot = Maths::Matrix4::rotate(t, 0, 1, 0) * Maths::Matrix4::rotate(0, 1, 0, 0);
		Maths::Matrix4 scale = Maths::Matrix4::scale(2, 2, 2);
		Maths::Matrix4 transform = offset * rot * scale;
		Maths::Matrix4 viewoffset = Maths::Matrix4::translate(camPos.x, camPos. y, camPos.z);

		float angle = rotx * ((float)M_PI / 180.0f);
		float xangle = cosf(angle);
		float zangle = sinf(angle);

		Maths::Matrix4 viewRotate = Maths::Matrix4::rotate(rotx, 0, 1, 0 ) * Maths::Matrix4::rotate(-roty, xangle, 0, zangle);
		Maths::Matrix4 invviewRotate = Maths::Matrix4::rotate(-rotx, 0, 1, 0 ) * Maths::Matrix4::rotate(roty, 1, 0, 0);
		Maths::Matrix4 camtransform = viewRotate * viewoffset;

		setUpShader(&shader, transform, camtransform, project, t);
		texture.bind();
		vao->bind();
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);
		Maths::Vector3 front = Maths::Vector3(0, 0, 1.0f);
		front = invviewRotate * front;
		front = front/front.length();
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if (Input::isKeyDown(GLFW_KEY_W))
			camPos = camPos + front*0.1f;
		if (Input::isKeyDown(GLFW_KEY_A))
			camPos = camPos - front.cross(Maths::Vector3::Up)*0.1f;
		if (Input::isKeyDown(GLFW_KEY_S))
			camPos = camPos - front*0.1f;
		if (Input::isKeyDown(GLFW_KEY_D))
			camPos = camPos + front.cross(Maths::Vector3::Up)*0.1f;
		if (Input::isKeyDown(GLFW_KEY_SPACE))
			camPos = Maths::Matrix4::translate(0, -0.1f, 0) * camPos;
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
			camPos = Maths::Matrix4::translate(0, 0.1f, 0) * camPos;
		rotx += mousex - oldmousex;
		while (rotx >= 360) rotx -= 360;
		while (rotx < 0) rotx += 360;
		roty += oldmousey - mousey;
		while (roty >= 360) roty -= 360;
		while (roty < 0) roty += 360;

		// t++;
		if (t > 360)
			t = 0;

		//end of stuff
		if (window.isfocused)
		{
			window.setCurrent();
		}
		window.update();
		oldmousex = mousex;
		oldmousey = mousey;
	}
	FreeImage_DeInitialise();
	return 0;
}