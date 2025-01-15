#include"Roof.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Roof::Roof(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Roof::drawCylinder(void) {

    GLUquadric* quad = gluNewQuadric();

    // Cylinder 1 top left
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.1f, 0.1f, 1.0f, 32, 32);
    glPopMatrix();

    // Cylinder 2 top right
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    glPushMatrix();
    glTranslatef(1.0f, 0.0f, -0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.1f, 0.1f, 1.0f, 32, 32);
    glPopMatrix();

    // Cylinder 3 left bottom
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.1f, 0.1f, 1.0f, 32, 32);
    glPopMatrix();

    // Cylinder 4 right bottom
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.1f, 0.1f, 1.0f, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(quad);
}

void Roof::drawBaseRoof(void) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    //Draw bottom
    glVertex3f(-1.2f, -0.1f, -0.6f);
    glVertex3f(1.2f, -0.1f, -0.6f);
    glVertex3f(1.2f, -0.1f, 0.6f);
    glVertex3f(-1.2f, -0.1f, 0.6f);

    //Draw top
    glVertex3f(-1.2f, 0.1f, -0.6f);
    glVertex3f(1.2f, 0.1f, -0.6f);
    glVertex3f(1.2f, 0.1f, 0.6f);
    glVertex3f(-1.2f, 0.1f, 0.6f);

    //Draw front
    glVertex3f(-1.2f, 0.1f, 0.6f);
    glVertex3f(1.2f, 0.1f, 0.6f);
    glVertex3f(1.2f, -0.1f, 0.6f);
    glVertex3f(-1.2f, -0.1f, 0.6f);

    //Draw back
    glVertex3f(-1.2f, 0.1f, -0.6f);
    glVertex3f(1.2f, 0.1f, -0.6f);
    glVertex3f(1.2f, -0.1f, -0.6f);
    glVertex3f(-1.2f, -0.1f, -0.6f);

    //Draw right
    glVertex3f(1.2f, 0.1f, -0.6f);
    glVertex3f(1.2f, 0.1f, 0.6f);
    glVertex3f(1.2f, -0.1f, 0.6f);
    glVertex3f(1.2f, -0.1f, -0.6f);

    //Draw left
    glVertex3f(-1.2f, 0.1f, -0.6f);
    glVertex3f(-1.2f, 0.1f, 0.6f);
    glVertex3f(-1.2f, -0.1f, 0.6f);
    glVertex3f(-1.2f, -0.1f, -0.6f);

    glEnd();
    glPopMatrix();
}

void Roof::draw(void)
{
	/*glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);*/

    //glBegin(GL_QUADS);

    //// Bottom face
    //glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    //glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    //glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front
    //glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front

    //// Top face
    //glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back
    //glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    //glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    //glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front

    //// Front face
    //glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front
    //glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front
    //glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    //glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front

    //// Back face
    //glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    //glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    //glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    //glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back

    //// Left face
    //glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    //glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back
    //glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front
    //glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front

    //// Right face
    //glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    //glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    //glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    //glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front

    //glEnd();
    //glPopMatrix();
    for (int i = 1; i <= 8; i++) {
        glPushMatrix();
        glTranslatef((float)(2 * i - 9), 0.0f, 0.0f);
        this->drawCylinder();
        this->drawBaseRoof();
        glPopMatrix();
    }

   /* this->drawCylinder();
    this->drawBaseRoof();*/
    
}