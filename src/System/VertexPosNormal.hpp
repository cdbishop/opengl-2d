#pragma once

#include<glm/glm.hpp>
#include <glad/glad.h>

struct VertexPosNormal {
	glm::vec3 Position;
	glm::vec3 Normal;

	static void Register() {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
	}
};