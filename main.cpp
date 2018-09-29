#define FREEIMAGE_LIB
#include <stdlib.h>
#include "Window.h"
#include "Shader.h"
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "FreeImage.h"
#include "Model.h"
#include "Camera.h"

#define WIDTH 1280.0f
#define HEIGHT 720.0f

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

void genMonkey(VertexArray *&vao, ElementBuffer *&ebo)
{
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
	genMonkey(vao, ebo);

	// Shader shader("Assets/Shader/vertex.glsl", "Assets/Shader/fragment.glsl");
	Shader shader("Assets/Shader/vertexCol.glsl", "Assets/Shader/fragmentCol.glsl");
	Texture texture("Assets/Img/leather.jpg");
	Camera camera(90, WIDTH / HEIGHT, 0.1f, 20);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float cols[300];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cols[i* 10 + j + 0] = (float)(rand() % 255) / 255;
			cols[i* 10 + j + 1] = (float)(rand() % 255) / 255;
			cols[i* 10 + j + 2] = (float)(rand() % 255) / 255;
		}
	}

	while (window.running)
	{
		if (checkGLError())
			return -1;
		window.clear();

		Maths::Matrix4 offset = Maths::Matrix4::translate(0, 0, 0);
		Maths::Matrix4 rot = Maths::Matrix4::rotate(0, 0, 1, 0) * Maths::Matrix4::rotate(0, 1, 0, 0);
		Maths::Matrix4 scale = Maths::Matrix4::scale(2, 2, 2);
		Maths::Matrix4 transform = offset * rot * scale;

		shader.use();
		shader.setMat4("projection_matrix", camera.Projection());
		shader.setMat4("view_matrix", camera.Transform());
		shader.setVec4("lightCol", Maths::Vector4(1, 1, 1, 1));
		shader.setVec3("lightPos", Maths::Vector3(0, 0, 1.0f));

		texture.bind();
		vao->bind();
		const int nMonkeys = 10;
		for (int i = 0; i < nMonkeys; i++)
		{
			for (int j = 0; j < nMonkeys; j++)
			{
				shader.setVec4("colour", Maths::Vector4(cols[i * nMonkeys + j + 0], cols[i * nMonkeys + j + 1], cols[i * nMonkeys + j + 2], 1));
				shader.setMat4("model_matrix", Maths::Matrix4::translate(2*i - nMonkeys + 1, 2*j - nMonkeys + 1, 0));
				glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);
			}
		}

		Maths::Vector3 front = camera.Front();
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if (Input::isKeyDown(GLFW_KEY_W))
			camera.move(0.1f, 0, 0);
		if (Input::isKeyDown(GLFW_KEY_A))
			camera.move(0, 0, -0.1f);
		if (Input::isKeyDown(GLFW_KEY_S))
			camera.move(-0.1f, 0, 0);
		if (Input::isKeyDown(GLFW_KEY_D))
			camera.move(0, 0, 0.1f);
		if (Input::isKeyDown(GLFW_KEY_SPACE))
			camera.move(0, 0.1f, 0);
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
			camera.move(0, -0.1f, 0);

		if (Input::mouseDragged())
			camera.rotate(Input::mouseDragX(), Input::mouseDragY());

		//end of stuff

		if (window.isfocused)
			window.setCurrent();
		window.update();
	}
	FreeImage_DeInitialise();
	return 0;
}