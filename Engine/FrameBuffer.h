#pragma once
#include <glad/glad.h>
#include <vector>
#include "Shader.h"

namespace Engine
{
class FrameBuffer
{
private:
  GLuint ID;
  int width;
  int height;
  GLuint depthBufID;
  std::vector<std::pair<std::string, GLuint>> bufferIDs;
  std::vector<unsigned int> attachments;

public:
  FrameBuffer(int width, int height);
  void addTextureBuffer(std::string name, GLenum attachment, GLint format, GLenum type);
  void setShader(Shader& shader);
  void bindTextures();
  inline void bind() { glBindFramebuffer(GL_FRAMEBUFFER, ID); }
  inline void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
  ~FrameBuffer();
};
}; // namespace Engine