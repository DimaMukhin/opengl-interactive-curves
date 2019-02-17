#pragma once

#include "common.h"

#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh(std::vector<glm::vec4> *vertices);

	void init(GLuint vertexPositionAttribLocation);

	void display();

	void display(int type);

	~Mesh();

private:
	GLuint VAO, VBO;
	std::vector<glm::vec4> *vertices;
};