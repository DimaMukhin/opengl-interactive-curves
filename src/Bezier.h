#pragma once

#include "common.h"
#include "ControlPoint.h"
#include "Mesh.h"

#include <vector>
#include <glm/glm.hpp>

class Bezier
{
public:
	Bezier(std::vector<ControlPoint*> *controlPoints, GLuint vertexPositionAttribLocation);

	void display();

	~Bezier();

private:
	std::vector<ControlPoint*> *controlPoints;
	std::vector<glm::vec4> *vertices;
	Mesh *curve;
	GLuint vertexPositionAttribLocation;

	void generateBezierCurve();
};