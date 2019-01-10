#include "Sprite.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <glad/glad.h>
#include <iostream>

Sprite::Sprite(const std::string& filepath)
  :_texture(0),
   _width(0),
  _height(0),
  _position(0.0f),
  _scale(1.0f),
  _colour(1.0f)
{
  //texture
  int nChannels, width, height;
  unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
  if (!data) {
    std::cerr << "Failed to load texture" << std::endl;
    throw std::runtime_error("Failed to load texture");
  }

  _width = width;
  _height = height;

  glGenTextures(1, &_texture);

  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}
