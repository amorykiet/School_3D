#include <iostream>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Cube.h"



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

using namespace std;
// Camera variables
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float movementSpeed = 0.1f;
float sensitivity = 100.0f;

//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH / 2.0);
float halfHeight = (float)(WINDOW_HEIGHT / 2.0);

void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
	glLoadIdentity();

	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
		cameraPosition.x + cameraOrientation.x, cameraPosition.y + cameraOrientation.y, cameraPosition.z + cameraOrientation.z,
		cameraUp.x, cameraUp.y, cameraUp.z);
	//Draw thing -------------------------------------------------------
	
	// Draw a Cube
	Cube cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	cube.draw();

	Cube cube2(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 45.0f, 0.0f), 1.5f);
	cube2.draw();

	//ae giup toi


	// End of drawing ---------------------------------------------------

	glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP:
		cameraPosition += movementSpeed * cameraOrientation;
		break;
	case GLUT_KEY_DOWN:
		cameraPosition -= movementSpeed * cameraOrientation;
		break;
	case GLUT_KEY_LEFT:
		cameraPosition -= glm::normalize(glm::cross(cameraOrientation, cameraUp)) * movementSpeed;
		break;
	case GLUT_KEY_RIGHT:
		cameraPosition += glm::normalize(glm::cross(cameraOrientation, cameraUp)) * movementSpeed;
		break;
	}

	glutPostRedisplay();
}


void mouseMove(int x, int y) {
	glutWarpPointer(halfWidth, halfHeight);
	float rotX = sensitivity * (float)(y - halfHeight) / WINDOW_HEIGHT;
	float rotY = sensitivity * (float)(x - halfWidth) / WINDOW_WIDTH;

	glm::vec3 newOrientation = glm::rotate(cameraOrientation, glm::radians(-rotX), glm::normalize(glm::cross(cameraOrientation, cameraUp)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(newOrientation, cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		cameraOrientation = newOrientation;
	}

	// Rotates the Orientation left and right
	cameraOrientation = glm::rotate(cameraOrientation, glm::radians(-rotY), cameraUp);
	glutPostRedisplay();
}


void processNormalKeys(unsigned char key, int xx, int yy) {


	if (key == 'w') {
		cameraPosition += movementSpeed * cameraOrientation;
	}
	else if (key == 's') {
		cameraPosition -= movementSpeed * cameraOrientation;
	}
	
	if (key == 'a') {
		cameraPosition -= glm::normalize(glm::cross(cameraOrientation, cameraUp)) * movementSpeed;
	}
	else if (key == 'd') {

		cameraPosition += glm::normalize(glm::cross(cameraOrientation, cameraUp)) * movementSpeed;
	}

	if (key == 32) {
		cameraPosition += movementSpeed * cameraUp;
	}
	else if (key == 'c') {
		cameraPosition -= movementSpeed * cameraUp;
	}

	if (key == 27)
		exit(0);

	glutPostRedisplay();
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	halfWidth = (float)(w / 2.0);
	halfHeight = (float)(h / 2.0);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("School");

	glutSetCursor(GLUT_CURSOR_NONE);

	// register callbacks
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(renderScene);
	glutPassiveMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}