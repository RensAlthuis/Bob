#pragma once
#include "Window.h"
#define FREEIMAGE_LIB
#include <FreeImage.h>
#include <iostream>

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
  void bind();
  void unbind();
};