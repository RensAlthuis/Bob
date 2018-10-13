#include "Texture.h"

namespace Engine{
Texture::Texture(const char *path)
{
	FREE_IMAGE_FORMAT formatobj = FreeImage_GetFileType(path, 0);
	FIBITMAP *image = FreeImage_Load(formatobj, path);
	FIBITMAP *temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);
	width = FreeImage_GetWidth(image);
	height = FreeImage_GetHeight(image);
	bits = FreeImage_GetBits(image);
	std::cout << width << " " << height << std::endl;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid *)bits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
}
};