#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec4> *vertices)
{
	this->vertices = vertices;
}

// initialize a new mesh
void Mesh::init(GLuint vertexPositionAttribLocation)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof((*vertices)[0]) * vertices->size(), &vertices->front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(vertexPositionAttribLocation);
	glVertexAttribPointer(vertexPositionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// unbind objects
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// display the mesh
void Mesh::display()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertices->size());

	glBindVertexArray(0);
}

// display the mesh with a certain type (example: GL_LINE_LOOP)
void Mesh::display(int type)
{
	glBindVertexArray(VAO);

	glDrawArrays(type, 0, vertices->size());

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
}
