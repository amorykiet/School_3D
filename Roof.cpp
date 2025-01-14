#include"Roof.h"

Roof::Roof(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Roof::draw(void)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);

    glBegin(GL_QUADS);

    // Bottom face
    glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front
    glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front

    // Top face
    glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back
    glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front

    // Front face
    glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front
    glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front
    glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front

    // Back face
    glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back

    // Left face
    glVertex3f(-8.0f, -0.5f, -0.5f); // Bottom-left back
    glVertex3f(-8.0f, 0.5f, -0.5f);  // Top-left back
    glVertex3f(-8.0f, 0.5f, 0.5f);   // Top-left front
    glVertex3f(-8.0f, -0.5f, 0.5f);  // Bottom-left front

    // Right face
    glVertex3f(8.0f, -0.5f, -0.5f);  // Bottom-right back
    glVertex3f(8.0f, 0.5f, -0.5f);   // Top-right back
    glVertex3f(8.0f, 0.5f, 0.5f);    // Top-right front
    glVertex3f(8.0f, -0.5f, 0.5f);   // Bottom-right front

    glEnd();

    glPopMatrix();
};