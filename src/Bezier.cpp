#include "Bezier.h"

Bezier::Bezier(std::vector<glm::vec4>* controlPoints)
{
	this->controlPoints = controlPoints;
	vertices = new std::vector<glm::vec4>();
}

void Bezier::init(GLuint vertexPositionAttribLocation)
{
}

void Bezier::display()
{
}

Bezier::~Bezier()
{
}

void Bezier::generateBezierCurve()
{
	glm::vec4 p0 = controlPoints[0];
	glm::vec4 p1 = controlPoints[1];
	glm::vec4 p2 = controlPoints[2];
	glm::vec4 p3 = controlPoints[3];

	for (float t = 0.0f; t <= 1.0001f; t += 0.1f) {
		GLfloat px = ((-1 * p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t*t*t) + ((3 * p0.x - 6 * p1.x + 3 * p2.x) * t*t) + ((-3 * p0.x + 3 * p1.x) * t) + p0.x;
		GLfloat py = ((-1 * p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t*t*t) + ((3 * p0.y - 6 * p1.y + 3 * p2.y) * t*t) + ((-3 * p0.y + 3 * p1.y) * t) + p0.y;
		GLfloat pz = 0.0f;

		vertices->push_back(glm::vec4(px, py, pz, 1.0f));
	}
}
