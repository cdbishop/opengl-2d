#include "Sprite.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>

Sprite::Sprite(const std::string& filepath)
    : _texture(0),
      _width(0),
      _height(0),
      _textureWidth(0),
      _textureHeight(0),
      _position(0.0f),
      _scale(1.0f),
      _colour(1.0f),
      _rotation(0.0f),
      _anchor(0.0f) {
  // texture
  int nChannels, width, height;
  unsigned char* data =
      stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
  if (!data) {
    std::cerr << "Failed to load texture" << std::endl;
    throw std::runtime_error("Failed to load texture");
  }

  _textureWidth = width;
  _textureHeight = height;

  _width = _textureWidth;
  _height = _textureHeight;

  glGenTextures(1, &_texture);

  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned int format = GL_RGB;
  switch (nChannels) {
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
    default:
      throw std::runtime_error("Unrecognised format");
  }
  glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Sprite::~Sprite() {}

void Sprite::UpdateBounds() {
  _boundingBox = std::make_shared<BoundingBox>(
      shared_from_this(), std::move(glm::vec2(GetWidth(), GetHeight())));
}
