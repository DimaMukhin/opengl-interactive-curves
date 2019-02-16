// Display a cube, using glDrawElements

#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const char *WINDOW_TITLE = "A2Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint modelUniformLocation, viewUniformLocation, projectionUniformLocation;

std::vector<glm::vec4>* generateBezierCurve(glm::vec4 *controlPoints, GLuint numOfControlPoints);

//----------------------------------------------------------------------------

// OpenGL initialization
void init()
{
   // Load shaders and use the resulting shader program
   GLuint program = InitShader("vshader.glsl", "fshader.glsl");
   glUseProgram(program);

   // set up vertex arrays
   GLuint vPosition = glGetAttribLocation(program, "vPosition");

   modelUniformLocation = glGetUniformLocation(program, "model");
   viewUniformLocation = glGetUniformLocation(program, "view");
   projectionUniformLocation = glGetUniformLocation(program, "projection");

   // setting default model transformation
   glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

   // setting default view transformation
   glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

   glm::vec4 cps[] = {
	   glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
	   glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
	   glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
	   glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
   };

   std::vector<glm::vec4> *vertices = generateBezierCurve(cps, 4);

   GLuint VAO;
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   GLuint VBO;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices->size(), &vertices->front(), GL_STATIC_DRAW);

   glEnableVertexAttribArray(vPosition);
   glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

// TODO: ask prof about how to convert this into matrix multiplication
std::vector<glm::vec4>* generateBezierCurve(glm::vec4 *controlPoints, GLuint numOfControlPoints)
{
	std::vector<glm::vec4> *vertices = new std::vector<glm::vec4>();
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

	return vertices;
}

//----------------------------------------------------------------------------

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glDrawArrays(GL_LINE_STRIP, 0, 11);

   glutSwapBuffers();
   glFinish();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
       case 033: // Escape Key
       case 'q': case 'Q':
          exit(EXIT_SUCCESS);
          break;
    }
}

//----------------------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
       switch(button) {
          
       }
    }
}

//----------------------------------------------------------------------------

void update(void)
{
}

//----------------------------------------------------------------------------

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);

   glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

   glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
