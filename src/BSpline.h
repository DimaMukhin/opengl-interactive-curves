#pragma once

#include "common.h"
#include "ControlPoint.h"
#include "Mesh.h"

#include <vector>
#include <glm/glm.hpp>

class BSpline
{
public:
	BSpline(std::vector<ControlPoint*> *controlPoints, GLuint vertexPositionAttribLocation);

	void display();

	void generateBSplineCurve();

	~BSpline();

private:
	std::vector<ControlPoint*> *controlPoints;
	std::vector<glm::vec4> *vertices;
	Mesh *curve;
	GLuint vertexPositionAttribLocation;
};