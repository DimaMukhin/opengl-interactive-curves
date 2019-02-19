#include "Bezier.h"

Bezier::Bezier(std::vector<ControlPoint*> *controlPoints, GLuint vertexPositionAttribLocation)
{
	this->controlPoints = controlPoints;
	this->vertexPositionAttribLocation = vertexPositionAttribLocation;
	vertices = new std::vector<glm::vec4>();
	generateBezierCurve();
}

void Bezier::display()
{
	curve->display(GL_LINE_STRIP);
}

Bezier::~Bezier()
{
}

// TODO: ask prof about how to convert this into matrix multiplication
void Bezier::generateBezierCurve()
{
	delete vertices;
	vertices = new std::vector<glm::vec4>();

	for (int i = 0; i + 3 < controlPoints->size(); i += 3) {
		glm::vec4 p0 = (*controlPoints)[i]->getLocation();
		glm::vec4 p1 = (*controlPoints)[i + 1]->getLocation();
		glm::vec4 p2 = (*controlPoints)[i + 2]->getLocation();
		glm::vec4 p3 = (*controlPoints)[i + 3]->getLocation();

		for (float t = 0.0f; t <= 1.0001f; t += 0.05f) {
			GLfloat px = ((-1 * p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t*t*t) + ((3 * p0.x - 6 * p1.x + 3 * p2.x) * t*t) + ((-3 * p0.x + 3 * p1.x) * t) + p0.x;
			GLfloat py = ((-1 * p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t*t*t) + ((3 * p0.y - 6 * p1.y + 3 * p2.y) * t*t) + ((-3 * p0.y + 3 * p1.y) * t) + p0.y;
			GLfloat pz = 0.0f;

			vertices->push_back(glm::vec4(px, py, pz, 1.0f));
		}
	}
	
	curve = new Mesh(vertices);
	curve->init(vertexPositionAttribLocation);
}
