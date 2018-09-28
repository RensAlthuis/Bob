#pragma once
#include <FreeImage.h>
#include <iostream>
#include <GLFW/glfw3.h>

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