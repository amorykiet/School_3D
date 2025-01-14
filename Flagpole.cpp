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

    //glPushMatrix();
    //glTranslatef(0.0f, 5.0f, 0.0f);

    /*glBegin(GL_QUADS);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            float x = i * 0.15f - 0.75f;
            float z = j * 0.15f - 0.75f;
            float wave = 0.1f * sinf(2.0f * M_PI * (x + 0.01f));

            glVertex3f(x, wave, z);
            glVertex3f(x + 0.15f, wave, z);
            glVertex3f(x + 0.15f, wave, z + 0.15f);
            glVertex3f(x, wave, z + 0.15f);
        }
    }
    glEnd();

    glPopMatrix();*/

}