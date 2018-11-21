#include "FrameBuffer.h"

namespace Engine
{
FrameBuffer::FrameBuffer(int width, int height)
    : width(width), height(height), bufferIDs()
{
    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);

    glGenRenderbuffers(1, &depthBufID);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufID);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addTextureBuffer(std::string name, GLenum attachment, GLint format, GLenum type)
{
    GLuint buf;
    glGenTextures(1, &buf);
    bufferIDs.push_back(std::pair<std::string, GLuint>(name, buf));
    attachments.push_back(attachment);
    glBindTexture(GL_TEXTURE_2D, buf);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, type, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, buf, 0);
    glDrawBuffers(attachments.size(), attachments.data());
}

void FrameBuffer::setShader(Shader &shader)
{
    shader.use();
    for (int i = 0; i < bufferIDs.size(); i++)
    {
        shader.setInt1(bufferIDs.at(i).first.c_str(), i);
    }
}

void FrameBuffer::bindTextures()
{
    for (int i = 0; i < bufferIDs.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, bufferIDs.at(i).second);
    }
}

FrameBuffer::~FrameBuffer()
{
    for (auto buf : bufferIDs)
    {
        glDeleteTextures(1, &buf.second);
    }
    glDeleteFramebuffers(1, &ID);
    glDeleteRenderbuffers(1, &depthBufID);
}

}; // namespace Engine
