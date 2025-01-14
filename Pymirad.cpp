#include "Pymirad.h"

Pymirad::Pymirad(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Pymirad::draw(void) {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);


    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);

    // top vertex
    glVertex3f(0.0f, 1.0f, 0.0f);
    // 1
    glVertex3f(-1.0f, 0.0f, 1.0f); // left bottom front
    glVertex3f(1.0f, 0.0f, 1.0f);  // right bottom front
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_TRIANGLES);

    //  2
    glVertex3f(0.0f, 1.0f, 0.0f);  // top vertex
    glVertex3f(1.0f, 0.0f, 1.0f);  // right bottom front
    glVertex3f(1.0f, 0.0f, -1.0f); // right bottom behind
    glEnd();

    glColor3f(0.7f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);
    //  3
    glVertex3f(0.0f, 1.0f, 0.0f);  // top vertex
    glVertex3f(1.0f, 0.0f, -1.0f); // right bottom behind
    glVertex3f(-1.0f, 0.0f, -1.0f);// left bottom behind
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES);
    //  4
    glVertex3f(0.0f, 1.0f, 0.0f);  // top vertex
    glVertex3f(-1.0f, 0.0f, -1.0f);// left bottom behind
    glVertex3f(-1.0f, 0.0f, 1.0f); // left bottom front
    glEnd();

    // base
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, 1.0f);  
    glVertex3f(1.0f, 0.0f, 1.0f);  
    glVertex3f(1.0f, 0.0f, -1.0f);  
    glVertex3f(-1.0f, 0.0f, -1.0f); 
    glEnd();

    glPopMatrix();
}