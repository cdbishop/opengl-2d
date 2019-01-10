#include "TexturedQuadScene.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>

#include "System/Application.hpp"
#include "System/ShaderManager.hpp"
#include "Math/Vector.hpp"

TexturedQuadScene::TexturedQuadScene()
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

TexturedQuadScene::~TexturedQuadScene()
{
	glDeleteVertexArrays(1, &_vertex_array);
	glDeleteBuffers(1, &_vertex_buffer);
}

void TexturedQuadScene::Init()
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
      
	//texture
	int nChannels;
	unsigned char* data = stbi_load("./data/textures/wall.jpg", &_width, &_height, &nChannels, 0);
	if (!data) {
		std::cerr << "Failed to load texture" << std::endl;
		throw std::runtime_error("Failed to load texture");
	}

	glGenTextures(1, &_texture);	

	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	_shader = GetApplication()->GetShaderManager()->CreateProgram("textured", "textured");
}

void TexturedQuadScene::Update()
{
}

void TexturedQuadScene::Render()
{	
	glBindTexture(GL_TEXTURE_2D, _texture);
	glUseProgram(_shader->GetId());
	_shader->SetUniformValue("inTexture", 0);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(_width, _height, 1.0f));
    _shader->SetUniformValuePtr("model", glm::value_ptr(model));
    _shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));
    _shader->SetUniformValue("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(_vertex_array);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
