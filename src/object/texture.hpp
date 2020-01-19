#pragma once

#include <string>

class Texture {
public:
  Texture(const std::string filepath);

  unsigned int Id() const { return _id; }

private:
  int _width;
  int _height;
  int _channels;
  unsigned int _id;
};