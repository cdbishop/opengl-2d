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
		{{ -1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		   -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		   0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f
		}}),
	_indices({
		0, 1, 2,
		1, 3, 2
		})
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

	glGenBuffers(1, &_index_buffer);
	
	glBindVertexArray(_vertex_array);

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

  _projection = glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
    static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f);

	//texture
	int width, height, nChannels;
	unsigned char* data = stbi_load("./data/textures/wall.jpg", &width, &height, &nChannels, 0);
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
  //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
  //_shader->SetUniformValuePtr("model", glm::value_ptr(model));
  //_shader->SetUniformValuePtr("projection", glm::value_ptr(_projection));
	glBindVertexArray(_vertex_array);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
