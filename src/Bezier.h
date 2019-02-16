#pragma once

#include "common.h"

#include <vector>
#include <glm/glm.hpp>

class Bezier
{
public:
	Bezier(std::vector<glm::vec4> *controlPoints);

	void init(GLuint vertexPositionAttribLocation);

	void display();

	~Bezier();

private:
	std::vector<glm::vec4> *controlPoints;
	std::vector<glm::vec4> *vertices;
	GLuint VAO, VBO;

	void generateBezierCurve();
};