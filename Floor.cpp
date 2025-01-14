#include "Cube.h"
#include "Floor.h"

Floor::Floor(glm::vec3 position, glm::vec3 rotation, float size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Floor::draw(void) {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size, size, size);

	// cube center
	Cube cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube1(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube10(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube11(glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	Cube cube2(glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube3(glm::vec3(-6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube4(glm::vec3(-8.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube5(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube6(glm::vec3(-12.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube7(glm::vec3(-14.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube8(glm::vec3(-16.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube9(glm::vec3(-18.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);


	Cube cube12(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube13(glm::vec3(8.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube14(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube15(glm::vec3(12.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube16(glm::vec3(14.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube17(glm::vec3(16.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube18(glm::vec3(18.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Cube cube19(glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);


	cube.draw();
	cube1.draw();
	cube2.draw();
	cube3.draw();
	cube4.draw();
	cube5.draw();
	cube6.draw();
	cube7.draw();
	cube8.draw();
	cube9.draw();
	cube10.draw();
	cube11.draw();
	cube12.draw();
	cube13.draw();
	cube14.draw();
	cube15.draw();
	cube16.draw();
	cube17.draw();
	cube18.draw();
	cube19.draw();

	glPopMatrix();
}