#pragma once
#include "Window.h"
#define FREEIMAGE_LIB
#include <FreeImage.h>
#include <iostream>

namespace Engine
{
class Texture
{

private:
  int width;
  int height;
  BYTE *bits;
  GLuint ID;

public:
  Texture(const char *path);
  ~Texture();
  inline void bind() { glBindTexture(GL_TEXTURE_2D, ID); }
  inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
};
}; // namespace Engine