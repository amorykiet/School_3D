#include"Flagpole.h"
#include<cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Flagpole::Flagpole(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Flagpole::draw(void) {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);

    GLUquadric* quad = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.1f, 0.1f, 5.0f, 32, 32);
    gluDeleteQuadric(quad);
    glPopMatrix();

    // Draw the rectangular flag on top
    glPushMatrix();
    glTranslatef(-0.75f, -0.5f, 0.0f);
    glBegin(GL_QUADS);

    //// Flag face
    glVertex3f(-0.75f, 0.5f, 0.0f);
    glVertex3f(0.75f, 0.5f, 0.0f);
    glVertex3f(0.75f, -0.5f, 0.0f);
    glVertex3f(-0.75f, -0.5f, 0.0f);

    glEnd();
    glPopMatrix();

}