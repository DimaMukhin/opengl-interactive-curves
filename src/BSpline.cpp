#include "BSpline.h"

BSpline::BSpline(std::vector<ControlPoint*> *controlPoints, GLuint vertexPositionAttribLocation)
{
	this->controlPoints = controlPoints;
	this->vertexPositionAttribLocation = vertexPositionAttribLocation;
	vertices = new std::vector<glm::vec4>();
	generateBSplineCurve();
}

// display the curve
void BSpline::display()
{
	curve->display(GL_LINE_STRIP);
}

BSpline::~BSpline()
{
}

// construct the curve
void BSpline::generateBSplineCurve()
{
	delete vertices;
	vertices = new std::vector<glm::vec4>();

	glm::mat4 coeficiants = glm::mat4(	-1.0f, 3.0f, -3.0f, 1.0f,
										3.0f, -6.0f, 3.0f, 0.0f,
										-3.0f, 0.0f, 3.0f, 0.0f,
										1.0f, 4.0f, 1.0f, 0.0f);


	for (int i = 0; i + 3 < controlPoints->size(); i++) {
		glm::vec4 p0 = (*controlPoints)[i]->getLocation();
		glm::vec4 p1 = (*controlPoints)[i + 1]->getLocation();
		glm::vec4 p2 = (*controlPoints)[i + 2]->getLocation();
		glm::vec4 p3 = (*controlPoints)[i + 3]->getLocation();

		glm::mat4 cpMatrix = glm::mat4(p0.x, p0.y, 0.0f, 1.0f,
			p1.x, p1.y, 0.0f, 1.0f,
			p2.x, p2.y, 0.0f, 1.0f,
			p3.x, p3.y, 0.0f, 1.0f);

		for (float t = 0.0f; t <= 1.0001f; t += 0.05f) {
			glm::mat4 tMatrix = glm::mat4(t*t*t, 0.0f, 0.0f, 0.0f,
				0.0f, t*t, 0.0f, 0.0f,
				0.0f, 0.0f, t, 0.0f,
				0.0f, 0.0f, 0.0f, 1);

			glm::mat4 res;
			res = res * cpMatrix;
			res = res * coeficiants;
			res = res * (1 / 6.0f);
			res = res * tMatrix;
			glm::vec4 finalVertex = glm::vec4(res[0][0] + res[1][0] + res[2][0] + res[3][0], res[0][1] + res[1][1] + res[2][1] + res[3][1], 0.0f, 1.0f);
			vertices->push_back(finalVertex);
		}
	}

	curve = new Mesh(vertices);
	curve->init(vertexPositionAttribLocation);
}
