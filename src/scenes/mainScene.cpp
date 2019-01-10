#include "mainScene.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>

#include "System/Application.hpp"
#include "System/ShaderManager.hpp"
#include "object/Sprite.hpp"
#include "Math/Vector.hpp"

MainScene::MainScene()
	:_vertices(
		{{ 0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
		}})
{
}

MainScene::~MainScene()
{
	glDeleteVertexArrays(1, &_vertex_array);
	glDeleteBuffers(1, &_vertex_buffer);
}

void MainScene::Init()
{
  glGenVertexArrays(1, &_vertex_array);
  glGenBuffers(1, &_vertex_buffer);

  glBindVertexArray(_vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  _projection = glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
    static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f);

  _sprite = std::make_shared<Sprite>("./data/textures/wall.jpg");

  _shader = GetApplication()->GetShaderManager()->CreateProgram("textured", "textured");
}

void MainScene::Update()
{
}

void MainScene::Render()
{	
  glBindTexture(GL_TEXTURE_2D, _sprite->GetTexture());
	glUseProgram(_shader->GetId());
	_shader->SetUniformValue("inTexture", 0);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(_sprite->GetPosition(), 0.0f));
    model = glm::scale(model, glm::vec3(_sprite->GetWidth(), _sprite->GetHeight(), 1.0f));
    _shader->SetUniformValuePtr("model", glm::value_ptr(model));
    _shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));
    _shader->SetUniformValue("spriteColor", _sprite->GetColour());
	glBindVertexArray(_vertex_array);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
