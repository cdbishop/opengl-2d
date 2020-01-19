#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct VertexPosTex {
  glm::vec3 Position;
  glm::vec2 TexCoord;

  static void Register() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
      (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
      (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
};