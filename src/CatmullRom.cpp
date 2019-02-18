#include "CatmullRom.h"

CatmullRom::CatmullRom(std::vector<ControlPoint*> *controlPoints, GLuint vertexPositionAttribLocation)
{
	this->controlPoints = controlPoints;
	this->vertexPositionAttribLocation = vertexPositionAttribLocation;
	vertices = new std::vector<glm::vec4>();
	generateCatmullRomCurve();
}

void CatmullRom::display()
{
	curve->display(GL_LINE_STRIP);
}

CatmullRom::~CatmullRom()
{
}

// TODO: ask prof about how to convert this into matrix multiplication
void CatmullRom::generateCatmullRomCurve()
{
	delete vertices;
	vertices = new std::vector<glm::vec4>();

	glm::mat4 coeficiants = glm::mat4(	2.0f, -2.0f, 1.0f, 1.0f,
										-3.0f, 3.0f, -2.0f, -1.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 conversion = glm::mat4(	0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										-0.5f, 0.0f, 0.5f, 0.0f,
										0.0f, -0.5f, 0.0f, 0.5f);


	for (int i = 0; i + 3 < controlPoints->size(); i++) {
		glm::vec4 p0 = (*controlPoints)[i]->getLocation();
		glm::vec4 p1 = (*controlPoints)[i + 1]->getLocation();
		glm::vec4 p2 = (*controlPoints)[i + 2]->getLocation();
		glm::vec4 p3 = (*controlPoints)[i + 3]->getLocation();

		glm::mat4 cpMatrix = glm::mat4(p0.x, p0.y, 0.0f, 1.0f,
			p1.x, p1.y, 0.0f, 1.0f,
			p2.x, p2.y, 0.0f, 1.0f,
			p3.x, p3.y, 0.0f, 1.0f);

		for (float t = 0.0f; t <= 1.0001f; t += 0.1f) {
			glm::mat4 tMatrix = glm::mat4(t*t*t, 0.0f, 0.0f, 0.0f,
				0.0f, t*t, 0.0f, 0.0f,
				0.0f, 0.0f, t, 0.0f,
				0.0f, 0.0f, 0.0f, 1);

			glm::mat4 res;
			res = res * cpMatrix;
			res = res * conversion;
			res = res * coeficiants;
			res = res * tMatrix;
			glm::vec4 finalVertex = glm::vec4(res[0][0] + res[1][0] + res[2][0] + res[3][0], res[0][1] + res[1][1] + res[2][1] + res[3][1], 0.0f, 1.0f);
			vertices->push_back(finalVertex);
		}
	}

	curve = new Mesh(vertices);
	curve->init(vertexPositionAttribLocation);
}
