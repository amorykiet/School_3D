#include "SampleBuilding.h"
#include "Cube.h"
#include "Floor.h"
#include "FrontFace.h"

SampleBuilding::SampleBuilding(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void SampleBuilding::draw(void) {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);
	
	//Cube cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	//Cube cube2(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	////Cube cube3(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	//cube.draw();
	//cube2.draw();
	////cube3.draw();

	GLUquadric* quad = gluNewQuadric();

	Floor floor1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Floor floor2(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Floor floor3(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Floor floor4(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	floor1.draw();
	floor2.draw();
	floor3.draw();
	floor4.draw();

	FrontFace frontFace(glm::vec3(0.0f, 6.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	frontFace.draw();

	// Vẽ hình trụ tại vị trí mới
	glPushMatrix();
	glTranslatef(1.0f, -1.0f, 1.5f); // Dịch chuyển hình trụ đến vị trí (1.0, 0.0, 1.0)
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Xoay hình trụ để dọc theo trục Y
	glColor3f(0.5f, 0.5f, 1.0f); // Màu xanh nhạt
	gluCylinder(quad, 0.1, 0.1, 2.0, 50, 50); // Vẽ hình trụ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0f, -1.0f, 2.5f); // Dịch chuyển hình trụ đến vị trí (1.0, 0.0, 1.0)
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Xoay hình trụ để dọc theo trục Y
	glColor3f(0.5f, 0.5f, 1.0f); // Màu xanh nhạt
	gluCylinder(quad, 0.1, 0.1, 2.0, 50, 50); // Vẽ hình trụ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f, -1.0f, 1.5f); // Dịch chuyển hình trụ đến vị trí (1.0, 0.0, 1.0)
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Xoay hình trụ để dọc theo trục Y
	glColor3f(0.5f, 0.5f, 1.0f); // Màu xanh nhạt
	gluCylinder(quad, 0.1, 0.1, 2.0, 50, 50); // Vẽ hình trụ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f, -1.0f, 2.5f); // Dịch chuyển hình trụ đến vị trí (1.0, 0.0, 1.0)
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Xoay hình trụ để dọc theo trục Y
	glColor3f(0.5f, 0.5f, 1.0f); // Màu xanh nhạt
	gluCylinder(quad, 0.1, 0.1, 2.0, 50, 50); // Vẽ hình trụ
	glPopMatrix();

	glPopMatrix();

	gluDeleteQuadric(quad);
}