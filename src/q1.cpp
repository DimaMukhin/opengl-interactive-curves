// Display a cube, using glDrawElements

#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "A2Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint modelUniformLocation, viewUniformLocation, projectionUniformLocation;

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

   
   GLuint numOfVertices = 1;
   glm::vec4 *controlPoints = new glm::vec4[numOfVertices] {
	   glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
   };

   GLuint numOfIndices = 1;
   GLuint *indices = new GLuint[numOfIndices] {
	   0
   };

   GLuint VAO;
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   GLuint IBO;
   glGenBuffers(1, &IBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

   GLuint VBO;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(controlPoints[0]) * numOfVertices, controlPoints, GL_STATIC_DRAW);

   glEnableVertexAttribArray(vPosition);
   glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);

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

   glm::mat4 projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f);

   glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
