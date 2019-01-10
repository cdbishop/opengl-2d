#include "SpriteManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>

SpriteManager::SpriteManager(Shader::Ptr shader, glm::mat4 projection)
  :_vertices(
    { { 0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
    } }),
  _shader(shader),
  _projection(projection)
{
  glGenVertexArrays(1, &_vertex_array);
  glGenBuffers(1, &_vertex_buffer);

  glBindVertexArray(_vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

SpriteManager::~SpriteManager()
{
  glDeleteVertexArrays(1, &_vertex_array);
  glDeleteBuffers(1, &_vertex_buffer);
}

void SpriteManager::Add(Sprite::Ptr sprite)
{
  _sprites.push_back(sprite);
}

void SpriteManager::Render()
{
  for (auto&& sprite : _sprites) {
    glBindTexture(GL_TEXTURE_2D, sprite->GetTexture());
    glUseProgram(_shader->GetId());
    _shader->SetUniformValue("inTexture", 0);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(sprite->GetPosition(), 0.0f));

    const auto offset = glm::vec2(sprite->GetAnchor().x * sprite->GetWidth(), sprite->GetAnchor().y * sprite->GetHeight());
    model = glm::translate(model, glm::vec3(offset, 0.0f));
    model = glm::rotate(model, sprite->GetRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(offset * -1.0f, 0.0f));

    model = glm::scale(model, glm::vec3(sprite->GetWidth(), sprite->GetHeight(), 1.0f));
    _shader->SetUniformValuePtr("model", glm::value_ptr(model));
    _shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));
    _shader->SetUniformValue("spriteColor", sprite->GetColour());
    glBindVertexArray(_vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }  
}
