#include <iostream>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include<stb/stb_image.h>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

using namespace std;
// Camera variables
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float movementSpeed = 0.2f;
float sensitivity = 100.0f;

//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH / 2.0);
float halfHeight = (float)(WINDOW_HEIGHT / 2.0);

GLuint loadTexture(const char* filename) {
	int width, height, channels;
	GLuint textureID;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (data == NULL) {
		printf("Failed to load image\n");
		exit(1);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return textureID;
}

// Texture
GLuint frontBuildingTex;
GLuint logoTex;
GLuint frontFaceTex;
GLuint groundTex;
GLuint flagTex;

GLuint skyboxTextures[6];

//Mat

void setDefaultMat() {
	GLfloat objAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat objDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat objSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, objAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, objSpecular);
}


void setFlagPillarMat() {
	GLfloat objAmbient[] = { 0.64f, 0.45f, 0.28f, 1.0f };
	GLfloat objDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat objSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, objAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, objSpecular);
}


void setWoodMat() {
	GLfloat objAmbient[] = { 0.26f, 0.16f, 0.05f, 1.0f };
	GLfloat objDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat objSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, objAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, objSpecular);
}


void setLeafMat() {
	GLfloat objAmbient[] = { 0.26f, 0.41f, 0.18f, 1.0f };
	GLfloat objDiffuse[] = { 0.2f, 0.4f, 0.2f, 1.0f };
	GLfloat objSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, objAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, objSpecular);
}


void loadAllTexture() {
	logoTex = loadTexture("texture\\bklogo.png");
	frontBuildingTex = loadTexture("texture\\front_building.png");
	frontFaceTex = loadTexture("texture\\front_face.png");
	groundTex = loadTexture("texture\\ground.jpg");
	flagTex = loadTexture("texture\\flag.png");

	//Skybox
	skyboxTextures[0] = loadTexture("texture\\skybox_right.png");
	skyboxTextures[1] = loadTexture("texture\\skybox_left.png");
	skyboxTextures[2] = loadTexture("texture\\skybox_up.png");
	skyboxTextures[3] = loadTexture("texture\\skybox_down.png");
	skyboxTextures[4] = loadTexture("texture\\skybox_front.png");
	skyboxTextures[5] = loadTexture("texture\\skybox_back.png");

}

GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

void initLighting() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

// Function to adjust light properties
void adjustLight(int key) {
	switch (key) {
	case 'z': // Decrease ambient light intensity
		light_ambient[0] = std::max(0.0f, light_ambient[0] - 0.1f);
		light_ambient[1] = std::max(0.0f, light_ambient[1] - 0.1f);
		light_ambient[2] = std::max(0.0f, light_ambient[2] - 0.1f);
		break;
	case 'x': // Increase ambient light intensity
		light_ambient[0] = std::min(0.8f, light_ambient[0] + 0.1f);
		light_ambient[1] = std::min(0.8f, light_ambient[1] + 0.1f);
		light_ambient[2] = std::min(0.8f, light_ambient[2] + 0.1f);
		break;
	default:
		break;
	}

	initLighting();
}


void drawCube(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	// Set material

	setDefaultMat();

	
	glBegin(GL_QUADS);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	// Top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// Bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();

	glPopMatrix();
}


void drawPillar(glm::vec3 position, GLfloat radius, GLfloat height, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x + 90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad, radius, radius, height, 50, 50);

	glPopMatrix();
}


void drawSky() {
	// Set material for the sky
	GLfloat skyAmbient[] = { 0.8f, 0.8f, 1.0f, 1.0f };
	GLfloat skyDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	GLfloat skySpecular[] = { 0.1f, 0.1f, 0.2f, 1.0f };
	GLfloat shininess = 5.0f; // Low shininess for a soft sky look

	glMaterialfv(GL_FRONT, GL_AMBIENT, skyAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, skyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, skySpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	// Draw the sky as a large sphere surrounding the scene
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f); // Centered at origin
	GLUquadric* skySphere = gluNewQuadric();
	gluSphere(skySphere, 60.0f, 50, 50); // Radius of 50
	gluDeleteQuadric(skySphere);
	glPopMatrix();

}


void drawSkybox() {

	glPushMatrix();

	glDisable(GL_DEPTH_TEST);
	GLfloat size = 50;

	// Set material for the sky
	GLfloat skyAmbient[] = { 0.8f, 0.8f, 1.0f, 1.0f };
	GLfloat skyDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	GLfloat skySpecular[] = { 0.1f, 0.1f, 0.2f, 1.0f };
	//GLfloat shininess = 5.0f; // Low shininess for a soft sky look

	glMaterialfv(GL_FRONT, GL_AMBIENT, skyAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, skyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, skySpecular);
	//glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glEnable(GL_TEXTURE_2D);

	// Right Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();

	// Left Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();


	// Up Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();

	// Down Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glEnd();


	// Front Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glEnd();

	// Back Face
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glEnd();


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

}


void drawRoof(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	// Set material

	setDefaultMat();


	drawCube(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0), glm::vec3(9.2f, 0.1f, 0.5f));

	for (glm::float32 i = 0; i < 10; i++)
	{
		drawPillar(glm::vec3(-5.0f + i, 0.5f, 0.0f), 0.05f, 0.5);
	}



	drawCube(glm::vec3(-6.25f, 0.0f, 0.0f), glm::vec3(0), glm::vec3(2.5f, 0.5f, 0.5f));
	drawCube(glm::vec3(5.25f, 0.0f, 0.0f), glm::vec3(0), glm::vec3(2.5f, 0.5f, 0.5f));

	glPopMatrix();
}


void drawSchool(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	// Set material

	setDefaultMat();


#pragma region Building

	glPushMatrix();
	glScalef(20, 4, 2);

	glEnable(GL_TEXTURE_2D);


	// Front face texture
	glBindTexture(GL_TEXTURE_2D, frontBuildingTex);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(20.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(20.0f, 4.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	// Back face texture
	glBindTexture(GL_TEXTURE_2D, frontBuildingTex);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f, -0.5f, -0.51f);
	glTexCoord2f(22.0f, 0.0f); glVertex3f(0.6f, -0.5f, -0.51f);
	glTexCoord2f(22.0f, 4.0f); glVertex3f(0.6f, 0.5f, -0.51f);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(-0.6f, 0.5f, -0.51f);

	glEnd();

	glDisable(GL_TEXTURE_2D);




	glBegin(GL_QUADS);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);


	// Back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	// Top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// Bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
	glPopMatrix();

#pragma endregion

#pragma region FrontFace

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frontFaceTex);
	glBegin(GL_QUADS);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, 2.01f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 2.01f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 2.0f, 2.01f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.01f);

	glEnd();


	glBindTexture(GL_TEXTURE_2D, logoTex);
	glBegin(GL_QUADS);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.1f, 0.3f, 2.01f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.9f, 0.3f, 2.01f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.9f, 1.6f, 2.01f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.1f, 1.6f, 2.01f);

	glEnd();


	glDisable(GL_TEXTURE_2D);


	drawCube(glm::vec3(0.0f, 0.5f, 1.5f), glm::vec3(0), glm::vec3(4, 3, 1));

	drawCube(glm::vec3(1.5f, -1.5f, 1.5f));

	drawCube(glm::vec3(-0.5f, -1.0f, 1.5f), glm::vec3(0), glm::vec3(3.5, 0.4, 2.4));
	
	drawPillar(glm::vec3(-2.0f, -1.0f, 2.5f), 0.08f, 1.0f);
	drawPillar(glm::vec3(-2.0f, -1.0f, 1.2f), 0.08f, 1.0f);

	drawPillar(glm::vec3(-1.0f, -1.0f, 2.5f), 0.08f, 1.0f);
	drawPillar(glm::vec3(-1.0f, -1.0f, 1.2f), 0.08f, 1.0f);

	drawPillar(glm::vec3(0.0f, -1.0f, 2.5f), 0.08f, 1.0f);
	drawPillar(glm::vec3(0.0f, -1.0f, 1.2f), 0.08f, 1.0f);

	drawPillar(glm::vec3(1.0f, -1.0f, 2.5f), 0.08f, 1.0f);
	drawPillar(glm::vec3(1.0f, -1.0f, 1.2f), 0.08f, 1.0f);

#pragma endregion

#pragma region Back

	glPushMatrix();
	glTranslatef(0.5f, 0.0f, 0.0f);


	drawCube(glm::vec3(-0.5f, -1.0f, -1.5f), glm::vec3(0), glm::vec3(3.5, 0.4, 2.4));


	drawCube(glm::vec3(-1.5f, -1.35f, -2.5f), glm::vec3(0), glm::vec3(1.5, 1.1, 0.2));

	drawPillar(glm::vec3(1.0f, -1.0f, -2.5f), 0.08f, 1.0f);
	drawPillar(glm::vec3(1.0f, -1.0f, -1.2f), 0.08f, 1.0f);

	glPopMatrix();
#pragma endregion

#pragma region Side

	setDefaultMat();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frontFaceTex);
	glBegin(GL_QUADS);

	// right side texture
	glNormal3f(-1.0f, 0.0f, 0.0f); // Normal pointing outwards
	glTexCoord2f(0.2f, 0.0f); glVertex3f(9.99f, -2.0f, 2.8f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(9.99f, 2.0f, 2.8f);
	glTexCoord2f(1.0f, 0.8f); glVertex3f(9.99f, 2.0f, 1.2f);
	glTexCoord2f(0.2f, 0.8f); glVertex3f(9.99f, -2.0f, 1.2f);

	// left side texture
	glNormal3f(1.0f, 0.0f, 0.0f); // Normal pointing outwards
	glTexCoord2f(0.2f, 0.0f); glVertex3f(-9.99f, -2.0f, 2.8f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-9.99f, 2.0f, 2.8f);
	glTexCoord2f(1.0f, 0.8f); glVertex3f(-9.99f, 2.0f, 1.2f);
	glTexCoord2f(0.2f, 0.8f); glVertex3f(-9.99f, -2.0f, 1.2f);

	glEnd();

	glDisable(GL_TEXTURE_2D);


	drawCube(glm::vec3(11.0f, -0.05f, 1.0f), glm::vec3(0), glm::vec3(2, 4.1, 4));
	drawCube(glm::vec3(-11.0f, -0.05f, 1.0f), glm::vec3(0), glm::vec3(2, 4.1, 4));


#pragma endregion

#pragma region Floor

	// floor
	drawCube(glm::vec3(0.0f, -2.0f, 0.2f), glm::vec3(0), glm::vec3(20, 0.2, 2.4));
	drawCube(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0), glm::vec3(5, 0.2, 6));

#pragma endregion

#pragma region Roof
	drawRoof(glm::vec3(0.0f, 2.0f, 0.0f));

	setFlagPillarMat();
	drawPillar(glm::vec3(0.0f, 5.0f, -0.5f), 0.025f, 5.0f);
	
	setDefaultMat();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, flagTex);
	glBegin(GL_QUADS);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 4.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.6f, 4.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.6f, 4.9f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 4.9f, -0.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);

#pragma endregion

	glPopMatrix();
}


void drawGround(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	// Set material

	setDefaultMat();


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTex);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f); // Normal pointing outwards
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-25.0f, -2.5f, -25.0f);
	glTexCoord2f(25.0f, 0.0f); glVertex3f(25.0f, -2.5f, -25.0f);
	glTexCoord2f(25.0f, 25.0f); glVertex3f(25.0f, -2.5f, 25.0f);
	glTexCoord2f(0.0f, 25.0f); glVertex3f(-25.0f, -2.5f, 25.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);


	
	//drawCube(glm::vec3(0.0f, -2.5f, 0.0f), glm::vec3(0), glm::vec3(50, 0.2, 50));


	glPopMatrix();
}


void drawTree(glm::vec3 position, GLfloat radius, GLfloat height, glm::vec3 rotation = glm::vec3(0), glm::vec3 size = glm::vec3(1)) {
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(size.x, size.y, size.z);

	setWoodMat();

	drawPillar(glm::vec3(0.0f, 0.0f, 0.0f), 0.15f, 1.5f);

	setLeafMat();

	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glutSolidCone(radius, height, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.0f);
	glutSolidCone(radius, height, 32, 32);


	setDefaultMat();

	glPopMatrix();

	glPopMatrix();
}


void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
		cameraPosition.x + cameraOrientation.x, cameraPosition.y + cameraOrientation.y, cameraPosition.z + cameraOrientation.z,
		cameraUp.x, cameraUp.y, cameraUp.z);
	

	GLfloat light_position[] = { 40.0f, 40.0f, 40.0f, 1.0f }; // Point light
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//drawSky();
	drawSkybox();

	//Draw thing -------------------------------------------------------


	drawGround(glm::vec3(0.0f, 0.5f, 0.0f));
	drawSchool(glm::vec3(0), glm::vec3(0), glm::vec3(1));
	drawTree(glm::vec3(5.0f, -1.5f, 3.5f), 1.0f, 2.0f, glm::vec3(0.0f), glm::vec3(0.5));
	drawTree(glm::vec3(8.0f, -1.5f, 3.5f), 1.0f, 2.0f, glm::vec3(0.0f), glm::vec3(0.5));
	drawTree(glm::vec3(-5.0f, -1.5f, 3.5f), 1.0f, 2.0f, glm::vec3(0.0f), glm::vec3(0.5));
	drawTree(glm::vec3(-8.0f, -1.5f, 3.5f), 1.0f, 2.0f, glm::vec3(0.0f), glm::vec3(0.5));

	//drawCube(glm::vec3(0), glm::vec3(0), glm::vec3(1));
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

	adjustLight(key);

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
	
	loadAllTexture();


	initLighting();

	// Enable normalization of normals
	glEnable(GL_NORMALIZE);

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