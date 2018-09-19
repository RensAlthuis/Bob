#include "Window.h"
#include "Shader.h"
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include <FreeImage.h>

#define WIDTH 1280.0f
#define HEIGHT 720.0f 

void checkGLError() {
		// check OpenGL error
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
}

void GenCube(VertexArray*& vao, ElementBuffer*& ebo) {
	float* vertices = new float[24*3]{
		 1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,	//front face
		-1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1, -1, //back face
		1, 1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1,		//right face
		-1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1, //left face
		1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1,		//top face
		1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1	//bottom face
	};

	float* uvs = new float[24*3]{
		 1, 1, 1, -1, -1, -1, -1, 1, //front
		 1, 1, 1, -1, -1, -1, -1, 1, //back
		 1, 1, 1, -1, -1, -1, -1, 1, //right
		 1, 1, 1, -1, -1, -1, -1, 1, //left
		 1, 1, 1, -1, -1, -1, -1, 1, //top
		 1, 1, 1, -1, -1, -1, -1, 1, //bottom
	};
	unsigned int* indices = new unsigned int[3*12]{
		0, 3, 1, 2, 1, 3,		// front face
		4, 7, 5, 6, 5, 7,		// back face
		8, 11, 9, 10, 9, 11,	// right face
		12, 15, 13, 14, 13, 15, // left face
		16, 19, 17, 18, 17, 19, // top face
		20, 23, 21, 22, 21, 23, // bottom face

	};
	ebo = new ElementBuffer(indices, 3*12);
	VertexBuffer* vbo = new VertexBuffer(vertices, 3*24, 3);
	VertexBuffer* ubo = new VertexBuffer(uvs, 2*24, 2);
	vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);
	vao->addBuffer(ubo, 1);
}

int main(void)
{

	Window window("something", WIDTH, HEIGHT);
	if (!window.init())
		return -1;


	VertexArray* vao;
	ElementBuffer* ebo;
	GenCube(vao, ebo);

	Shader shader("Shader/vertex.glsl", "Shader/fragment.glsl");

	 //Maths::Matrix4 project = Maths::Matrix4::ortho(0, 16, 0, 9, -10, 20);
	Maths::Matrix4 project = Maths::Matrix4::perspective(90, WIDTH/HEIGHT, 0.1f, 10.0f);
	Maths::Matrix4 view = Maths::Matrix4::translate(0,0, -3.0f);

	FREE_IMAGE_FORMAT formatobj = FreeImage_GetFileType("leather.jpg", 0);
	FIBITMAP* image = FreeImage_Load(formatobj, "leather.jpg");
	FIBITMAP * temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);
	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);
	BYTE* bits = FreeImage_GetBits(image);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)bits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int t = 0;
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	while (window.running)
	{
		checkGLError();
		window.clear();

		//stuff here

		Maths::Matrix4 offset = Maths::Matrix4::translate(0, 0, 0);
		Maths::Matrix4 rot = Maths::Matrix4::rotate(0, 0, 1, 0) * Maths::Matrix4::rotate(0, 1, 0, 0);
		Maths::Matrix4 scale = Maths::Matrix4::scale(2,2,2);
		Maths::Matrix4 transform = offset * rot * scale;

		shader.use();
		shader.setMat4("projection_matrix", project);
		shader.setMat4("view_matrix", view);
		shader.setMat4("model_matrix", transform * Maths::Matrix4::translate(0, 0, 0.0));
		shader.setVec4("lightCol", Maths::Vector4(1, 1, 1, 1));
		shader.setVec3("lightPos", Maths::Vector3(0, 0, -1.0f ) * Maths::Matrix4::rotate(-t, 0, 1, 0) );
		shader.setInt1("tex", 0);

		vao->bind();
		glDrawElements(GL_TRIANGLES, ebo->elementCount, GL_UNSIGNED_INT, 0);

		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		if(Input::isKeyDown(GLFW_KEY_W))
			view = view * Maths::Matrix4::translate(0,0,0.1f);
		if(Input::isKeyDown(GLFW_KEY_A))
			view = view * Maths::Matrix4::translate(0.1f,0,0);
		if(Input::isKeyDown(GLFW_KEY_S))
			view = view * Maths::Matrix4::translate(0,0,-0.1f);
		if(Input::isKeyDown(GLFW_KEY_D))
			view = view * Maths::Matrix4::translate(-0.1f,0,0);
		if(Input::isKeyDown(GLFW_KEY_SPACE))
			view = view * Maths::Matrix4::translate(0,-0.1f,0);
		if(Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
			view = view * Maths::Matrix4::translate(0,0.1f,0);

		t++;
		if (t > 360) t == 0;

		//end of stuff
		if(window.isfocused){
			window.setCurrent();
		}
		window.update();

	}

	return 0;
}