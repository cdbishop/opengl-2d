#include "UIManager.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>

UIManager::UIManager(Shader::Ptr shader, glm::mat4 projection)
    : _vertices({{0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

                  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f}}),
      _shader(shader),
      _projection(projection) {
  glGenVertexArrays(1, &_vertex_array);
  glGenBuffers(1, &_vertex_buffer);
  glBindVertexArray(_vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

UIManager::~UIManager() {
  glDeleteVertexArrays(1, &_vertex_array);
  glDeleteBuffers(1, &_vertex_buffer);
}

void UIManager::Add(Sprite::Ptr sprite) { _sprites.push_back(sprite); }

void UIManager::Remove(Sprite::Ptr sprite) {
  _sprites.erase(
      std::find_if(_sprites.begin(), _sprites.end(),
                   [&sprite](Sprite::Ptr item) { return item == sprite; }),
      _sprites.end());
}

void UIManager::Render() {
  glBindVertexArray(_vertex_array);

  for (auto&& sprite : _sprites) {
    glBindTexture(GL_TEXTURE_2D, sprite->GetTexture());
    glUseProgram(_shader->GetId());
    _shader->SetUniformValue("inTexture", 0);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(sprite->GetPosition(), 0.0f));

    const auto offset =
        glm::vec2(sprite->GetAnchor().x * sprite->GetTextureWidth(),
                  sprite->GetAnchor().y * sprite->GetTextureHeight());
    model = glm::translate(model, glm::vec3(offset, 0.0f));
    model =
        glm::rotate(model, sprite->GetRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(offset * -1.0f, 0.0f));

    model = glm::scale(
        model, glm::vec3(sprite->GetWidth(), sprite->GetHeight(), 1.0f));
    _shader->SetUniformValuePtr("model", glm::value_ptr(model));
    _shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));
    _shader->SetUniformValue("spriteColor", sprite->GetColour());
    _shader->SetUniformValue("repeatFactorU",
                             static_cast<float>(sprite->GetWidth()) /
                                 static_cast<float>(sprite->GetTextureWidth()));
    _shader->SetUniformValue(
        "repeatFactorV", static_cast<float>(sprite->GetHeight()) /
                             static_cast<float>(sprite->GetTextureHeight()));
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
