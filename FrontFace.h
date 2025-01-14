#pragma once

#include <GL/glut.h>

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class FrontFace {
public:
	FrontFace(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), float size = 1.0f);
	void draw(void);

private:
	glm::vec3 position;
	glm::vec3 rotation;
	float size;

};