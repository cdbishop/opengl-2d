#include "texture.hpp"

#include "../external/stb_image.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

Texture::Texture(const std::string filepath) {
  // texture
  unsigned char* data =
      stbi_load(filepath.c_str(), &_width, &_height, &_channels, 0);
  if (!data) {
    throw std::runtime_error("Failed to load texture");
  }

  glGenTextures(1, &_id);

  glBindTexture(GL_TEXTURE_2D, _id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}
